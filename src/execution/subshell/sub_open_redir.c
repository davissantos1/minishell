/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_open_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:25:33 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 14:14:18 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	open_redir(char *file, int flags);

void	sub_redirection(t_minishell *shell, t_subshell *sub)
{
	t_redir	*redir;

	if (!sub->redir)
		return ;
	//tira esse void pf
	(void) shell;
	redir = sub->redir;
	while (redir)
	{
		if (redir->type == APPEND)
			sub->std_out = open_redir(redir->file,
					O_CREAT | O_APPEND | O_WRONLY);
		else if (redir->type == REDOUT)
			sub->std_out = open_redir(redir->file,
					O_CREAT | O_TRUNC | O_WRONLY);
		else if (redir->type == REDIN)
			sub->std_in = open_redir(redir->file, O_RDONLY);
		redir = redir->next;
	}
	if (sub->std_in < 0 || sub->std_out < 0)
		sub_close_redir(sub);
}

static int	open_redir(char *file, int flags)
{
	int		fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}
