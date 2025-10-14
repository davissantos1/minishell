/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:51:19 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 18:46:19 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_bin(t_minishell *shell, char *command, char **envp);
static char	**put_endbar(t_minishell *shell, char **envp);

void	path(t_minishell *shell, t_cmd *cmd)
{
	char	*temp;

	temp = search_bin(shell, cmd->argv[0], shell->env);
	if (temp == NULL)
		return ;
	cmd->argv[0] = temp;
	if (!gc_addptr(temp, shell->gc, GC_CUSTOM3))
		exit_code(shell, errno);
}

static char	*search_bin(t_minishell *shell, char *command, char **envp)
{
	char		*bin;
	static char	**paths;
	int			i;

	i = 1;
	if (!paths)
	{
		paths = put_endbar(shell, envp);
		shell->paths = &paths;
	}
	if (ft_strchr(command, '/') && access(command, F_OK) == 0)
		return (ft_strdup(command));
	while (paths && paths[i])
	{
		bin = ft_strjoin(paths[i], command);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

static char	**put_endbar(t_minishell *shell, char **envp)
{
	int		i;
	int		j;
	char	*temp;
	char	**paths;

	i = 0;
	j = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	envp[i][4] = ':';
	paths = ft_split(envp[i], ':');
	if (!paths)
		return (NULL);
	while (paths[j])
	{
		temp = ft_strjoin(paths[j], "/");
		free(paths[j]);
		paths[j] = temp;
		j++;
	}
	envp[i][4] = '=';
	if (!gc_addmtx(paths, shell->gc, GC_CUSTOM3))
		exit_code(shell, errno);
	return (paths);
}
