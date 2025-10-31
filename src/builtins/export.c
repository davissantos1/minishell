/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:53:11 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/31 08:33:40 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **env);
static void	print_vars(t_minishell *shell, t_cmd *cmd);
static void	maybe_add(t_minishell *shell, char *var);
static int	no_value(t_minishell *shell, char *str);

void	export_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	*tmp_var;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!cmd->argv[1])
		print_vars(shell, cmd);
	while (cmd->argv[i + 1])
	{
		i++;
		if (!nvalid(cmd->argv[i], &ret) && !no_value(shell, cmd->argv[i]))
		{
			maybe_add(shell, cmd->argv[i]);
			tmp_var = get_env(shell->tmp_var, cmd->argv[i]);
			if (!tmp_var)
				continue ;
			tmp_var = tmp_var - ft_strlen(cmd->argv[i]) - 1;
			shell->tmp_var = ft_mtxdel(shell->tmp_var, tmp_var);
			if (!shell->tmp_var
				|| !gc_addptr(shell->tmp_var, shell->gc, GC_LOCALVARS))
				exit_code(shell, errno);
		}
	}
	pid_add(shell, NOT_FORKED, NOT_FORKED, ret << 8);
}

static void	print_vars(t_minishell *shell, t_cmd *cmd)
{
	char	**env;
	char	**tmp_vars;
	int		fd;

	env = ft_mtxdup(shell->env);
	fd = 1;
	if (!shell->lstfd)
		fd = cmd->std_out;
	if (!env)
		return ;
	tmp_vars = shell->tmp_var;
	sort_env(env);
	sort_env(tmp_vars);
	print_mtx(env, fd);
	print_mtx(shell->tmp_var, fd);
	ft_mtxfree(env);
}

static int	no_value(t_minishell *shell, char *str)
{
	char	**new_tmp;
	char	*var;

	if (ft_strchr(str, '='))
		return (0);
	if (get_env(shell->tmp_var, str) || get_env(shell->env, str))
		return (1);
	var = ft_strdup(str);
	if (!var || !gc_addptr(var, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	new_tmp = ft_mtxadd(shell->tmp_var, var);
	if (!new_tmp || !gc_addptr(new_tmp, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	shell->tmp_var = new_tmp;
	return (1);
}

static void	sort_env(char **env)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	len = ft_mtxlen(env);
	i = 0;
	j = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	maybe_add(t_minishell *shell, char *var)
{
	char	*env_var;
	char	*cpy_var;
	char	*tmp;

	tmp = ft_strchr(var, '=');
	cpy_var = ft_strdup(var);
	if (!cpy_var || !gc_addptr(cpy_var, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	*tmp = '\0';
	if (*(tmp - 1) != '+')
		return (add_var(shell, cpy_var));
	*(tmp - 1) = '\0';
	env_var = get_env(shell->env, var);
	remove_plus(var, cpy_var);
	if (!env_var)
		return (add_var(shell, cpy_var));
	var = ft_strjoin(env_var - ft_strlen(var) - 1, tmp + 1);
	if (!var || !gc_addptr(var, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	add_var(shell, var);
}
