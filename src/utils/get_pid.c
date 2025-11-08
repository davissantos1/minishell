/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:41:20 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/08 19:25:20 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pid(t_minishell *shell)
{
	struct dirent	*cur;
	DIR				*dir;
	int				i;
	char			*pid;

	i = 0;
	pid = ft_calloc(10, sizeof(char));
	if (!pid)
		exit_code(shell, errno);
	dir = opendir("/proc/self/task");
	if (!dir)
		return (pid);
	while (i < 3)
	{
		cur = readdir(dir);
		if (!cur)
			return (pid);
		i++;
	}
	ft_strlcpy(pid, cur->d_name, 10);
	closedir(dir);
	return (pid);
}
