/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:16:55 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 21:16:23 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_code(t_minishell *shell, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (code == EXIT_FAILURE)
		perror("minishell");
	else if (code == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(shell->error, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (shell)
		gc_free_all(shell->gc);
	exit(code);
}

void	error_code(t_minishell *shell, int code)
{
	if (!shell->error)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (code == EXIT_FAILURE)
		perror("minishell");
	else if (code == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(shell->error, 2);
		ft_putstr_fd("'\n", 2);
	}
	shell->exit = code;
	shell->error = NULL;
}
