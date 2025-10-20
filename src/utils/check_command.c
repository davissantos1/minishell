/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:01:22 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 15:21:29 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(t_minishell *shell, t_cmd *cmd)
{
	char	*file;

	file = cmd->argv[0];
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit = 127;
		return (0);
	}
	if (access(file, X_OK) == -1)
	{
		perror(file);
		shell->exit = 126;
		return (0);
	}
	return (1);
}
