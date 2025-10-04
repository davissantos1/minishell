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

static int	open_redir(char *file, int flags);

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
			cmd->std_out = open_redir(redir->file,
					O_CREAT | O_APPEND | O_RDWR);
		else if (redir->type == NODE_REDOUT)
			cmd->std_out = open_redir(redir->file,
					O_CREAT | O_TRUNC | O_RDWR);
		else if (redir->type == NODE_REDIN)
			cmd->std_in = open_redir(redir->file, O_RDONLY);
		else
			cmd->std_in = heredoc(redir->file);
		lst = lst->next;
	}
}

static int	open_redir(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}
