/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:31:10 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/23 14:31:21 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_nums(char *str);
static void	just_exit(t_minishell *shell, t_cmd *cmd);

void	exit_builtin(t_minishell *shell, t_cmd *cmd)
{
	if (cmd->std_out == 1)
		ft_putendl_fd("exit", 2);
	just_exit(shell, cmd);
	ft_putstr_fd("exit: too many arguments\n", 2);
	pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
}

static void	just_exit(t_minishell *shell, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (cmd->argv[1] && only_nums(cmd->argv[1]))
		ret = (unsigned int)ft_atoi(cmd->argv[1]) % 256;
	else if (cmd->argv[1])
	{
		ret = 2;
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	if (ret != 2 && cmd->argv[1] && cmd->argv[2])
		return ;
	gc_free_all(shell->gc);
	exit(ret);
}

static int	only_nums(char *str)
{
	if (*str == '+' || *str == '-')
	{
		str++;
		if (!*str)
			return (0);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
