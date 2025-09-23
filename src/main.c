/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:32:47 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/23 08:10:58 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void) ac;
	(void) av;
	(void) env;
	while (1)
	{
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf("exit");
			break ;
		}
		if (*str != '\0')
			add_history(str);
		printf("voce digitou: %s\n", str);
	}
	rl_clear_history();
	return (0);
}
