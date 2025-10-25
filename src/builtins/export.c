/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:53:11 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/21 16:14:55 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **env);
static void	print_vars(t_minishell *shell);
static void	maybe_add(t_minishell *shell, char *var, int *ret);
static int	without_value(t_minishell *shell, char *str, int *ret);

void	export_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	*tmp_var;
	int		i;
	int		ret;
	
	i = 1;
	ret = 0;
	if (!cmd->argv[1])
		print_vars(shell);
	while (cmd->argv[i])
	{
		if (!without_value(shell, cmd->argv[i], &ret))
		{
			maybe_add(shell, cmd->argv[i], &ret);
			tmp_var = get_env(shell->tmp_var, cmd->argv[i]);
			if (tmp_var)
			{
				tmp_var = tmp_var - ft_strlen(cmd->argv[i]) - 1;
				shell->tmp_var = ft_mtxdel(shell->tmp_var, tmp_var);
				if (!shell->tmp_var || !gc_addptr(shell->tmp_var, shell->gc, GC_LOCALVARS))
					exit_code(shell, errno);
			}
		}
		i++;
	}
	pid_add(shell, NOT_FORKED, NOT_FORKED, ret << 8);
}

static void	print_vars(t_minishell *shell)
{
	char	**env;
	char	**tmp_vars;
	int		i;

	env = ft_mtxdup(shell->env);
	i = 0;
	if (!env)
		return ;
	tmp_vars = shell->tmp_var;
	sort_env(env);
	sort_env(tmp_vars);
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
	while (*tmp_vars)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(*tmp_vars, 1);
		tmp_vars++;
	}
	ft_mtxfree(env);
}

static int	without_value(t_minishell *shell, char *str, int *ret)
{
	char	**new_tmp;
	char	*var;

	if (!ft_isalpha(*str))
	{
		*ret = 1;
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (0);
	}
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
	*ret = 0;
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

static void	maybe_add(t_minishell *shell, char *var, int *ret)
{
	char	*gvar;
	char	*tmp;

	*ret = 0;
	tmp = ft_strchr(var, '=');
	var = ft_strdup(var);
	if (!var || !gc_addptr(var, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	if (!ft_isalpha(*var))
	{
		*ret = 1;
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return ;
	}
	*tmp = '\0';
	if (*(tmp - 1) != '+')
		return (add_var(shell, var));
	*(tmp - 1) = '\0';
	gvar = get_env(shell->env, var);
	if (!gvar)
		return (add_var(shell, var));
	var = ft_strjoin(gvar, tmp + 1);
	if (!var || gc_addptr(var, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	add_var(shell, var);
}
