/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:16:11 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 17:19:29 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var(t_minishell *shell, char *var);

void	unset_builtin(t_minishell *shell, t_cmd *cmd)
{
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("unset: Too many arguments\n", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1  << 8);
		return ;
	}
	if (!cmd->argv[1])
	{
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
		return ;
	}
	remove_var(shell, cmd->argv[1]);
}

static void	remove_var(t_minishell *shell, char *var)
{
	char	**new_env;
	char	*ptr_env;

	ptr_env = get_env(shell->env, var);
	if (!ptr_env)
	{
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
		return ;
	}
	ptr_env = ptr_env - ft_strlen(var) - 1;
	new_env = ft_mtxdel(shell->env, ptr_env);
	if (!new_env)
		exit_code(shell, errno);
	if (new_env != shell->env)
	{
		if (!gc_addptr(new_env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
	shell->env = new_env;
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}
