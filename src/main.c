/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:32:47 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/21 09:39:18 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_read(t_minishell *shell, char *input)
{
	errno = 0;
	if (!input)
		shell->input = readline("\033[091mMinishell$ \033[0m");
	else
		shell->input = input;
	if (!shell->input)
	{
		if (errno != 0)
			exit_code(shell, EXIT_FAILURE);
		printf("exit\n");
		return (-1);
	}
	if (!gc_addptr(shell->input, shell->gc, GC_TEMP))
		exit_code(shell, EXIT_FAILURE);
	add_history(shell->input);
	return (0);
}

int	shell_process(t_minishell *shell, char *input)
{
	if (shell_read(shell, input) == -1)
		return (-1);
	lexer(shell);
	token_validate(shell);
	if (shell->error || !shell->head )
	{
		error_code(shell, 2);
		return (0);
	}
	else if (!shell->head || !shell->head->value)
		return (0);
	else
		parser(shell);
	//token_print(shell);
	//ast_print(shell->root);
	handler(shell);
	shell->head = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*shell;
	int			status;

	shell = shell_init(env);
	register_parent_signals();
	if (ac == 1)
	{
		while (1)
		{
			if (shell_process(shell, NULL) == -1)
				break ;
			shell->head = gc_free_tag(shell->gc, GC_TOKEN);
			shell->root = gc_free_tag(shell->gc, GC_AST);
		}
	}
	else
	{
		shell_process(shell, av_convert(shell, av));
	}
	rl_clear_history();
	status = shell->exit + g_signal;
	gc_free_all(shell->gc);
	return (status);
}
