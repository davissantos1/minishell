/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:16:48 by vitosant          #+#    #+#             */
/*   Updated: 2025/09/30 17:43:36 by dasimoes         ###   ########.fr       */
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
	shell->path = getcwd(NULL, 0);
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
	return (shell);
}
