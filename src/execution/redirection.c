/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:40:01 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/30 10:16:06 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_cmd *cmd, char *file, int flags);

void	redirection(t_minishell *shell, t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd->redir)
		return ;
	redir = cmd->redir;
	while (redir)
	{
		if (cmd->std_out != -1 && redir->type == APPEND)
			cmd->std_out = open_redir(cmd, redir->file,
					O_CREAT | O_APPEND | O_WRONLY);
		else if (cmd->std_out != -1 && redir->type == REDOUT)
			cmd->std_out = open_redir(cmd, redir->file,
					O_CREAT | O_TRUNC | O_WRONLY);
		else if (cmd->std_in != -1 && redir->type == REDIN)
			cmd->std_in = open_redir(cmd, redir->file, O_RDONLY);
		redir = redir->next;
	}
	if (cmd->std_in < 0 || cmd->std_out < 0)
		close_redir(shell, cmd);
}

static int	open_redir(t_cmd *cmd, char *file, int flags)
{
	int		fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		perror(file);
	if (flags == O_RDONLY && cmd->std_in != 0)
		close(cmd->std_in);
	else if (flags != O_RDONLY && cmd->std_out != 1)
		close(cmd->std_out);
	return (fd);
}
