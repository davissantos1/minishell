/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:01:22 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 17:17:17 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int 	is_dir(char *file);

int	check_command(t_cmd *cmd, int *i)
{
	char		*file;

	file = cmd->argv[0];
	if (cmd->is_builtin >= 0)
		return (1);
	if (access(file, F_OK) == -1 || !ft_strchr(file, '/'))
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", 2);
		*i = 127;
		return (0);
	}
	if (access(file, X_OK) == -1 || is_dir(file))
	{
		perror(file);
		*i = 126;
		return (0);
	}
	return (1);
	
}

static int 	is_dir(char *file)
{
	struct stat	sfile;

	stat(file, &sfile);
	if ((sfile.st_mode & TYPE_MASK) == DIR_MASK)
		return (1);
	return (0);
}
