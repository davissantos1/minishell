/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:44:54 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/08 16:13:57 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	disco(t_minishell *shell, char *dir);
static void	update_env(t_minishell *shell, char olddir[PATH_MAX]);
static void	remove_vars(t_minishell *shell);
static char	*expand_ddot(t_minishell *shell);

void	cd_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	*varhome;

	if (!cmd->argv[1])
	{
		varhome = get_env(shell->env, "HOME");
		if (!varhome)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
			return ;
		}
		if (chdir(varhome) == -1)
			perror("cd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
	}
	else if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("cd: Too many arguments\n", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
	}
	else
		disco(shell, cmd->argv[1]);
}

static void	disco(t_minishell *shell, char *dir)
{
	char	olddir[PATH_MAX];

	ft_bzero(olddir, PATH_MAX);
	ft_memmove(olddir, "OLDPWD=", 7);
	getcwd(olddir + 7, PATH_MAX - 7);
	if (!ft_strcmp(dir, ".."))
		dir = expand_ddot(shell);
	else if (!ft_strcmp("-", dir))
		dir = get_env(shell->env, "OLDPWD");
	if (!dir || chdir(dir) == -1)
	{
		if (dir)
			perror("cd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, (dir != 0) << 8);
		return ;
	}
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
	update_env(shell, olddir);
}

static void	update_env(t_minishell *shell, char olddir[PATH_MAX])
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

	v_env = get_env(shell->env, "PWD");
	if (v_env)
	{
		v_env = v_env - 1 - 3;
		shell->env = ft_mtxdel(shell->env, v_env);
		if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
	v_env = get_env(shell->env, "OLDPWD");
	if (v_env)
	{
		v_env = v_env - 1 - 6;
		shell->env = ft_mtxdel(shell->env, v_env);
		if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
}

static char	*expand_ddot(t_minishell *shell)
{
	char	parent_dir[PATH_MAX];
	char	*ret_dir;
	char	*last_slash;

	ft_bzero(parent_dir, PATH_MAX);
	if (!getcwd(parent_dir, PATH_MAX))
		exit_code(shell, errno);
	last_slash = ft_strrchr(parent_dir, '/');
	if (ft_strcmp("/", parent_dir))
		*last_slash = '\0';
	ret_dir = ft_strdup(parent_dir);
	if (!ret_dir || !gc_addptr(ret_dir, shell->gc, GC_AST))
		exit_code(shell, errno);
	return (ret_dir);
}
