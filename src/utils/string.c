/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:45:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/05 13:52:27 by dasimoes         ###   ########.fr       */
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

int	match_str(char *input, char *match)
{
	if (*input == '\0')
		return (*match == '\0');
	if (*input == '*')
	{
		if (match_str(input + 1, match))
			return (1);
		if (*match && *match != *input)
			return (match_str(input, match + 1));
		return (0);
	}
	if (*match && *match == *input)
		return (match_str(input + 1, match + 1));
	return (0);
}
