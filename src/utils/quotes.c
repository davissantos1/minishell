/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:55:20 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/08 21:09:01 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_quotes(char *str, char quotes)
{
	int	index;

	index = 0;
	if (!str || !*str)
		return (0);
	while (str[index])
	{
		if (str[index] != quotes)
			return (0);
		index++;
	}
	return (1);
}

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

int	word_size(char *token, char quotes)
{
	int	index;
	int	size;

	size = 0;
	index = 0;
	while (token[index])
	{
		if (token[index] != quotes)
			size++;
		index++;
	}
	return (size);
}

char	*remove_quotes(t_minishell *s, char *t)
{
	char	*result;
	char	quote;
	int		open;
	int		j;

	j = -1;
	open = 0;
	quote = '\0';
	result = gc_calloc((ft_strlen(t) + 1), s->gc, GC_TOKEN);
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (*t)
	{
		if ((*t == '\'' || *t == '\"') && !open)
		{
			open = 1;
			quote = *t;
		}
		else if (quote == *t && open)
			open = 0;
		if (*t != quote)
			result[++j] = *t;
		t++;
	}
	return (result);
}
