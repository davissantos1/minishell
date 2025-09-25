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

void	exit_code(t_minishell *shell, int code)
{
	if (shell)
		gc_free_all(shell->gc);
	if (code != 0)
		perror("minishell");
	exit(code);
}

t_minishell	*shell_init(char **env)
{
	t_gc 		*garbage;
	t_minishell	*shell;

	garbage = gc_init();
	if (!garbage)
		exit_code(NULL, EXIT_FAILURE);
	shell = gc_malloc(sizeof(t_minishell), garbage, GC_DEFAULT);
	if (!shell)
		exit_code(NULL, EXIT_FAILURE);
	shell->gc = garbage;
	shell->tokens = NULL;
	shell->root = NULL;
	shell->env = env;
	shell->fd0 = dup(STDIN_FILENO);
	shell->fd1 = dup(STDOUT_FILENO);
	shell->fd2 = dup(STDERR_FILENO);
	if (shell->fd0 == -1 || shell->fd1 == -1 || shell->fd2 == -1) 
		exit_code(shell, EXIT_FAILURE);
	shell->exit = 0;
	return (shell);
}

int	shell_process(t_minishell *shell)
{
	char *input;

	errno = 0;
	input = readline("minishell$ ");
	if (!input)
	{
		if (errno != 0)
			exit_code(shell, EXIT_FAILURE);
		else
			return (-1);
	}
	if (*input)
		add_history(input);
	printf("voce digitou: %s\n", input);
	free(input);
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
