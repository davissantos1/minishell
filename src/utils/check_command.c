/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:01:22 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/07 12:04:49 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(t_cmd *cmd)
{
	char	*file;

	file = cmd->argv[0];
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	if (access(file, X_OK) == -1)
	{
		perror(file);
		return (0);
	}
	return (1);
}
