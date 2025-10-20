/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:53:11 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 09:32:55 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char **argv);
static void	add_var(t_minishell *shell, t_cmd *cmd);

void	export_builtin(t_minishell *shell, t_cmd *cmd)
{
	int	valid;

	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("export: Too many arguments", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1  << 8);
		return ;
	}
	valid = is_valid(cmd->argv);
	if (valid)
		add_var(shell, cmd);
	else
	{
		ft_putstr_fd("export: Invalid argument", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1  << 8);
	}	
}

static int	is_valid(char **argv)
{
	int	j;

	j = 0;
	while(ft_isalnum(argv[1][j]))
		j++;
	if (argv[1][j] == '=')
		j++;
	while(ft_isalnum(argv[1][j]))
		j++;
	if (argv[1][j] == '\0')
		return (1);
	return (0);
}

static void	add_var(t_minishell *shell, t_cmd *cmd)
{
	char	*var;
	char	*exists;
	char	*equal;

	var = ft_strdup(cmd->argv[1]);
	if (!var || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	equal = ft_strchr(cmd->argv[1], '=');
	*equal = '\0';
	exists = get_env(shell, cmd->argv[1]);
	if (exists)
	{
		exists = exists - ft_strlen(cmd->argv[1]) - 2;
		shell->env = ft_mtxdel(shell->env, exists);
		if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
	shell->env = ft_mtxadd(shell->env, var);
	if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
}
