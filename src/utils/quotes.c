/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:55:20 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/03 11:21:49 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*remove_quotes(t_gc *gc, char *token)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = gc_malloc(word_size(token) * sizeof(char), gc, GC_TOKEN);
	if (!result)
		return (NULL);
	while (token[i])
	{
		if (token[i] != '\'' && token[i] != '\"')
		{
			result[j] = token[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
