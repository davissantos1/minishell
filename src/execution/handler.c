/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:14:39 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 17:06:54 by vitosant         ###   ########.fr       */
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
	gc_free_tag(shell->gc, GC_PIDLIST);
	gc_free_tag(shell->gc, GC_FDLIST);
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
// 	node = gc_calloc(sizeof(t_ast), shell->gc, GC_FDLIST);
// 	node->type = NODE_OR;
// 	shell->root = node;
// 	node = gc_calloc(sizeof(t_ast), shell->gc, GC_FDLIST);
// 	node->type = NODE_CMD;
// 	cmd = gc_calloc(sizeof(t_cmd), shell->gc, GC_FDLIST);
// 	cmd->std_in = 0;
// 	cmd->std_out = 1;
// 	cmd->redir = gc_calloc(sizeof(t_list), shell->gc, GC_FDLIST);
// 	redir = gc_calloc(sizeof(t_redir), shell->gc, GC_FDLIST);
// 	redir->type = NODE_HEREDOC;
// 	redir->file = ft_strdup("teste_heredoc");
// 	gc_addptr(redir->file, shell->gc, GC_FDLIST);
// 	cmd->redir->content = redir;
// 	cmd->argv = ft_split("/bin/cat -e", ' ');
// 	gc_addptr(redir->file, shell->gc, GC_FDLIST);
// 	node->data = cmd;
// 	shell->root->left = node;
// 	// cmd 2
// 	cmd = gc_calloc(sizeof(t_cmd), shell->gc, GC_FDLIST);
// 	cmd->std_in = 0;
// 	cmd->std_out = 1;
// 	cmd->argv = ft_split("/bin/cat -e", ' ');
// 	shell->root->right = gc_calloc(sizeof(t_ast), shell->gc, GC_FDLIST);
// 	shell->root->right->data = cmd;
// 	handler(shell);
// 	gc_free_all(shell->gc);
// 	printf ("shell exit: %i", shell->exit);
// 	return (0);
// }
