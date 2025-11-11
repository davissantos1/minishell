/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:18:46 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/11 08:55:48 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_heredoc(t_minishell *shell, t_ast *node)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = node->data;
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
	{
		redir = cmd->redir;
		while (redir && !g_signal)
		{
			if (redir->type == HEREDOC)
			{
				if (cmd->std_in != 0)
					close(cmd->std_in);
				cmd->std_in = heredoc(shell, remove_quotes(shell, redir->file));
			}
			redir = redir->next;
		}
		return ;
	}
	if (node->left && !g_signal)
		find_heredoc(shell, node->left);
	if (node->right && !g_signal)
		find_heredoc(shell, node->right);
	if (g_signal && (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
		&& cmd->std_in > 0)
		close(cmd->std_in);
}
