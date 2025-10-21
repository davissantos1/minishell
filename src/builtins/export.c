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

static int	is_valid(char **argv);

void	export_builtin(t_minishell *shell, t_cmd *cmd)
{
	int	valid;

	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("export: Too many arguments\n", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1  << 8);
		return ;
	}
	if (!cmd->argv[1])
	{
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
		return ;
	}
	valid = is_valid(cmd->argv);
	if (valid)
		add_var(shell, cmd->argv[1]);
	else
	{
		ft_putstr_fd("export: Invalid argument\n", 2);
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
	else
		return (0);
	while(ft_isalnum(argv[1][j]))
		j++;
	if (argv[1][j] == '\0')
		return (1);
	return (0);
}

