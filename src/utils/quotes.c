/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:55:20 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/11 15:28:03 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	maybe_remove(char *str)
{
	int	squote;
	int	dquote;
	int	i;

	i = -1;
	squote = 0;
	dquote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !squote)
			squote++;
		else if (str[i] == '\'' && squote)
			squote--;
		else if (str[i] == '\"' && !dquote)
			dquote++;
		else if (str[i] == '\"' && dquote)
			dquote--;
		if (str[i] == '\'' && str[i + 1] == '\'' && (squote || dquote))
			return (0);
		if (str[i] == '\'' && str[i + 1] == '\'' && (squote || dquote))
			return (0);
	}
	return (1);
}

char	*remove_enclosed_quotes(t_minishell *s, char *str)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	result = gc_calloc((ft_strlen(str) + 1), s->gc, GC_TOKEN);
	if (!result)
		exit_code(s, EXIT_FAILURE);
	if (!maybe_remove(str))
		return (str);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + 1] && str[i] == str[i + 1])
				i++;
			else
				result[++j] = str[i];
		}
		else
			result[++j] = str[i];
	}
	return (result);
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
