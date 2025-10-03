/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:45:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/03 19:26:59 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*av_convert(t_minishell *s, char **av)
{
	char	*conv;
	char	*temp;
	int		index;

	index = 1;
	conv = ft_strdup("\0");
	while (av[index])
	{
		temp = conv;
		conv = ft_strjoin(conv, av[index]);
		if (!conv)
			exit_code(s, EXIT_FAILURE);
		free(temp);
		temp = conv;
		conv = ft_strjoin(conv, " ");
		if (!conv)
			exit_code(s, EXIT_FAILURE);
		free(temp);
		index++;
	}
	if (!gc_addptr(conv, s->gc, GC_TEMP))
		exit_code(s, EXIT_FAILURE);
	return (conv);
}

