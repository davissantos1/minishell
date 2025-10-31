/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:25:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/31 08:21:29 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_echo(t_minishell *shell, t_cmd *cmd, char **argv, int endln);

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
				just_echo(shell, cmd, &cmd->argv[i], put_endln);
				return (pid_add(shell, NOT_FORKED, NOT_FORKED, 0));
			}
			j++;
		}
		put_endln = 0;
		i++;
	}
	just_echo(shell, cmd, &cmd->argv[i], put_endln);
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}

static void	just_echo(t_minishell *shell, t_cmd *cmd, char **argv, int endln)
{
	int	fd;
	int	i;

	i = 0;
	fd = 1;
	if (!shell->lstfd)
		fd = cmd->std_out;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (endln)
		ft_putchar_fd('\n', fd);
}
