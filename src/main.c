/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:32:47 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/23 08:10:58 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_process(t_minishell *shell)
{
	errno = 0;
	shell->input = readline("minishell$ ");
	if (!shell->input)
	{
		if (errno != 0)
			exit_code(shell, EXIT_FAILURE);
		else
			return (-1);
	}
	if (!gc_addptr(shell->input, shell->gc, GC_DEFAULT))
		exit_code(shell, EXIT_FAILURE);
	if (*shell->input)
		add_history(shell->input);
	printf("voce digitou: %s\n", shell->input);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*shell;

	(void) ac;
	(void) av;
	shell = shell_init(env);
	while (1)
	{
		if(shell_process(shell) == -1)
			break;
	}
	rl_clear_history();
	gc_free_all(shell->gc);
	return (0);
}
