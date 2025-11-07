/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:16:48 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/07 15:59:24 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*shell_init(char **env)
{
	t_gc		*garbage;
	t_minishell	*shell;

	garbage = gc_init();
	if (!garbage)
		exit_code(NULL, EXIT_FAILURE);
	shell = gc_calloc(sizeof(t_minishell), garbage, GC_SHELL);
	if (!shell)
		exit_code(NULL, EXIT_FAILURE);
	shell->gc = garbage;
	shell->path = ft_strjoin(getenv("HOME"), "/bin/minishell");
	shell->tmp_var = gc_calloc(sizeof(char *), garbage, GC_LOCALVARS);
	if (!shell->path)
		exit_code(shell, EXIT_FAILURE);
	if (!gc_addptr(shell->path, shell->gc, GC_SHELL))
		exit_code(shell, EXIT_FAILURE);
	shell->env = env;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->std_err = dup(STDERR_FILENO);
	if (shell->std_in == -1 || shell->std_out == -1 || shell->std_err == -1)
		exit_code(shell, EXIT_FAILURE);
	shell->exit = 0;
	shell->name = "Minishell";
	return (shell);
}

t_ast	*ast_create(t_minishell *s)
{
	t_ast	*node;

	node = gc_calloc(sizeof(t_ast), s->gc, GC_AST);
	if (!node)
		exit_code(s, EXIT_FAILURE);
	return (node);
}

t_cmd	*cmd_create(t_minishell *s, int ac)
{
	t_cmd	*cmd;

	cmd = gc_calloc(sizeof(t_cmd), s->gc, GC_CMD);
	if (!cmd)
		exit_code(s, EXIT_FAILURE);
	cmd->argv = gc_calloc(sizeof(char *) * (ac + 1), s->gc, GC_CMD);
	if (!cmd->argv)
		exit_code(s, EXIT_FAILURE);
	cmd->std_out = 1;
	return (cmd);
}
