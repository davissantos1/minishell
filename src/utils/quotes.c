/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:55:20 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/26 13:48:54 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_single_quotes(char *str)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			count++;
		index++;
	}
	return (count);
}

int	check_quotes(char *token)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			s++;
		if (token[i] == '\"')
			d++;
		i++;
	}
	if (s % 2 != 0 || d % 2 != 0)
		return (0);
	return (1);
}

int	word_size(char *token)
{
	int index;
	int	size;

	size = 0;
	index = 0;
	while (token[index])
	{
		if (token[index] != '\'' && token[index] != '\"')
			size++;
		index++;
	}
	return (size);
}

char	*remove_quotes(t_minishell *s, char *t)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = gc_malloc(word_size(t) * sizeof(char), s->gc, GC_TOKEN);
	if (!result)
		exit_code(s, 2);
	while (t[i])
	{
		if (t[i] != '\'' && t[i] != '\"')
		{
			result[j] = t[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
