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
static void	close_redir(t_cmd *cmd);

void	redirection(t_minishell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*lst;

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
		lst = lst->next;
	}
	if (cmd->std_in < 0 || cmd->std_out < 0)
		close_redir(cmd);
}

static int	open_redir(t_minishell *shell, char *file, int flags)
{
	int		fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}
