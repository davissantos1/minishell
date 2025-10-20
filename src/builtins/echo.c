/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:25:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/20 16:54:12 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_minishell *shell, t_cmd *cmd)
{
	int	i;
	int	j;
	int	put_endln;

	i = 1;
	put_endln = 1;
	while (cmd->argv[i] && cmd->argv[i][0] == '-' && cmd->argv[i][1])
	{
		j = 1;
		while (cmd->argv[i][j])
		{
			if (ft_strchr("n", cmd->argv[i][j]) == NULL)
			{
				just_echo(&cmd->argv[i], put_endln);
				return ;
			}
			j++;
		}
		put_endln = 0;
		i++;
	}
	just_echo(&cmd->argv[i], put_endln);
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}

static void	just_echo(char **argv, int put_endln)
{
	int	i;

	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (put_endln)
		ft_putchar_fd('\n', 1);
}
