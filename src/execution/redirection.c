/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:40:01 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 17:26:23 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(char *file, int flags);
static int	there_is_heredoc(t_redir *redir);

void	redirection(t_minishell *shell, t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd->redir)
		return ;
	//tira esse void pf
	(void) shell;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == APPEND && !there_is_heredoc(cmd->redir))
			cmd->std_out = open_redir(redir->file,
					O_CREAT | O_APPEND | O_WRONLY);
		else if (redir->type == REDOUT)
			cmd->std_out = open_redir(redir->file,
					O_CREAT | O_TRUNC | O_WRONLY);
		else if (redir->type == REDIN && !there_is_heredoc(cmd->redir))
			cmd->std_in = open_redir(redir->file, O_RDONLY);
		redir = redir->next;
	}
	if (cmd->std_in < 0 || cmd->std_out < 0)
		close_redir(cmd);
}

static int	open_redir(char *file, int flags)
{
	int		fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}

static int	there_is_heredoc(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}
