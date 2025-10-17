/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:25:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/10 11:47:35 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(t_minishell *shell, char *str, int put_endl);
static void	print_str(t_minishell *shell, char *str, int put_endl);

void	echo(t_minishell *shell, t_cmd *cmd)
{
	int	put_endl;

	put_endl = 1;
	cmd->argv++;
	while (cmd->argv && cmd->argv[0] == '-')
	{
		if (cmd->argv[1] == 'n')
			put_endl = 0;
		cmd->argv++;
	}
	while (cmd->argv)
	{
		if(cmd->argv[0] == '$')
			print_var(shell, cmd->argv, put_endl);
		else
			print_str(shell, cmd->argv, put_endl);
		cmd->argv++;
	}
}

static void	print_var(t_minishell *shell, char *str, int put_endl)
{
	char	*str;

	str = get_env(shell->env, str + 1);
}
