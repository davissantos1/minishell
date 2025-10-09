/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:14:39 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/07 08:08:07 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(t_minishell *shell)
{
	find_heredoc(shell, shell->root);
	if (shell->exit == 130)
		return ;
	executor(shell, shell->root);
	if (shell->lst_pid)
		shell->exit = get_return(shell);
}


// int main(int ac, char **av, char **env)
// {
// 	t_minishell	*shell;
// 	t_ast	*node;
// 	t_cmd	*cmd;
// 	t_redir	*redir;

// 	(void) ac;
// 	(void) av;
// 	shell = shell_init(env);
// 	node = gc_calloc(sizeof(t_ast), shell->gc, GC_CUSTOM1);
// 	node->type = NODE_PIPE;
// 	shell->root = node;
// 	node = gc_calloc(sizeof(t_ast), shell->gc, GC_CUSTOM1);
// 	node->type = NODE_CMD;
// 	cmd = gc_calloc(sizeof(t_cmd), shell->gc, GC_CUSTOM1);
// 	cmd->redir = gc_calloc(sizeof(t_list), shell->gc, GC_CUSTOM1);
// 	redir = gc_calloc(sizeof(t_redir), shell->gc, GC_CUSTOM1);
// 	redir->type = NODE_HEREDOC;
// 	redir->file = ft_strdup("teste_heredoc");
// 	gc_addptr(redir->file, shell->gc, GC_CUSTOM1);
// 	cmd->redir->content = redir;
// 	redir = gc_calloc(sizeof(t_redir), shell->gc, GC_CUSTOM1);
// 	redir->type = NODE_APPEND;
// 	redir->file = ft_strdup("teste");
// 	cmd->redir->next = gc_calloc(sizeof(t_list), shell->gc, GC_CUSTOM1);
// 	gc_addptr(redir->file, shell->gc, GC_CUSTOM1);
// 	cmd->redir->next->content = redir;
// 	node->data = cmd;
// 	shell->root->left = node;
// 	handler(shell);
// 	gc_free_all(shell->gc);
// 	return (0);
// }
