/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:18:46 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 17:29:25 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_heredoc(t_minishell *shell, t_ast *node)
{
	t_cmd	*cmd;
	t_redir	*redir;

	if (node->type == NODE_CMD && shell->exit != 130)
	{
		cmd = node->data;
		redir = cmd->redir;
		while (redir && shell->exit != 130)
		{
			if (redir->type == HEREDOC)
				cmd->std_in = heredoc(redir->file);
			redir = redir->next;
		}
		return ;
	}
	if (node->left && shell->exit != -130)
		find_heredoc(shell, node->left);
	if (node->right && shell->exit != -130)
		find_heredoc(shell, node->right);
}
