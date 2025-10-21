/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:44:54 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/21 16:19:49 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	disco(t_minishell *shell, char *dir);
static void	update_env(t_minishell *shell, char	olddir[PATH_MAX]);
static void	remove_vars(t_minishell *shell);

void	cd_builtin(t_minishell *shell, t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
		return ;
	}
	else if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("cd: Too many arguments\n", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
		return ;
	}
	disco(shell, cmd->argv[1]);
}

static void	disco(t_minishell *shell, char *dir)
{
	size_t	len;
	char	olddir[PATH_MAX];

	len = ft_strlen(dir);
	ft_bzero(olddir, PATH_MAX);
	ft_memmove(olddir, "OLDPWD=", 7);
	getcwd(olddir + 7, PATH_MAX - 7);
	if (ft_strncmp(&dir[len - 2], "\\ ", 2) != 0)
		dir[len - 1] = '\0';
	if (chdir(dir) == -1)
	{
		perror("cd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
		return ;
	}
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
	update_env(shell, olddir);
}

static void	update_env(t_minishell *shell, char	olddir[PATH_MAX])
{
	char	dir[PATH_MAX];

	ft_bzero(dir, PATH_MAX);
	ft_memmove(dir, "PWD=", 4);
	getcwd(dir + 4, PATH_MAX - 4);
	remove_vars(shell);
	add_var(shell, olddir);
	add_var(shell, dir);
}

static void	remove_vars(t_minishell *shell)
{
	char	*v_env;

	v_env = get_env(shell, "PWD");
	if (v_env)
	{
		v_env = v_env - 2 - 3;
		shell->env = ft_mtxdel(shell->env, v_env);
		if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
	v_env = get_env(shell, "OLDPWD");
	if (v_env)
	{
		v_env = v_env - 2 - 6;
		shell->env = ft_mtxdel(shell->env, v_env);
		if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
}