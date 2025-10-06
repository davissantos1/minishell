/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:40:01 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/03 11:40:03 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_minishell *shell, char *file, int flags);
static void	add_err(t_minishell *shell, t_err *node);

void	do_redir(t_minishell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*lst;

	(void) shell;
	if (!cmd->redir)
		return ;
	lst = cmd->redir;
	while (lst)
	{
		redir = lst->content;
		if (redir->type == NODE_APPEND)
			cmd->std_out = open_redir(shell, redir->file,
					O_CREAT | O_APPEND | O_WRONLY);
		else if (redir->type == NODE_REDOUT)
			cmd->std_out = open_redir(shell, redir->file,
					O_CREAT | O_TRUNC | O_WRONLY);
		else if (redir->type == NODE_REDIN)
			cmd->std_in = open_redir(shell, redir->file, O_RDONLY);
		else
			cmd->std_in = heredoc(redir->file);
		lst = lst->next;
	}
}

static int	open_redir(t_minishell *shell, char *file, int flags)
{
	int		fd;
	char	*error;
	t_err	*node;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		error = strerror(errno);
		node = gc_calloc(sizeof(t_err), shell->gc, GC_CUSTOM1);
		if (!node)
			exit_code(shell, errno);
		node->file = file;
		node->error_msg = ft_strdup(error);
		if (!node->error_msg)
			exit_code(shell, errno);
		gc_addptr(node->error_msg, shell->gc, GC_CUSTOM1);
		add_err(shell, node);
	}
	return (fd);
}

static void	add_err(t_minishell *shell, t_err *node)
{
	t_err	*last_node;

	last_node = shell->redir_err;
	if (!last_node)
	{
		shell->redir_err = node;
		return ;
	}
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = node;
}
