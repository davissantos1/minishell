/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:16:55 by vitosant          #+#    #+#             */
/*   Updated: 2025/09/30 15:08:06 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_code(t_minishell *shell, int code)
{
	ft_putstr_fd("minishell: " , 2);
	if (shell)
		gc_free_all(shell->gc);
	if (code == EXIT_FAILURE)
		perror("minishell");
	else if (code == 2)
		ft_putstr_fd(shell->error, 2);
	exit(code);
}
