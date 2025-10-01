/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:32:47 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/30 20:14:27 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_process(t_minishell *shell)
{
	errno = 0;
	shell->input = readline("\033[091mMinishell$ \033[0m");
	if (!shell->input)
	{
		if (errno != 0)
			exit_code(shell, EXIT_FAILURE);
		else
			return (-1);
	}
	if (!gc_addptr(shell->input, shell->gc, GC_TEMP))
		exit_code(shell, EXIT_FAILURE);
	if (*shell->input)
		add_history(shell->input);
	lexer(shell);
	//parser(shell);
	// call execution function
	token_print(shell);
	gc_free_tag(shell->gc, GC_TOKEN);
	shell->head = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*shell;
	int			status;

	(void) ac;
	(void) av;
	shell = shell_init(env);
	while (1)
	{
		if (shell_process(shell) == -1)
			break ;
	}
	rl_clear_history();
	status = shell->exit + shell->signal;
	gc_free_all(shell->gc);
	return (status);
}
