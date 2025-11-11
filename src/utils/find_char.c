/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:31:06 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/11 16:09:44 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_last_quote(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] != '\'' && str[index] != '\"')
			return (&str[index - 1]);
	}
	return (&str[index]);
}

char	*find_break(char *str)
{
	size_t	i;

	i = 0;
	if (!*str)
		return (str);
	if (str[0] == '\'' || str[0] == '\"')
		return (find_last_quote(str));
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?' || ft_isdigit(str[i + 1]))
				return (&str[i + 2]);
			if (str[i + 1] == '$')
				return (&str[i + 2]);
		}
		if (str[i] == '\'' || str[i] == '\"')
			return (&str[i - 1]);
		if (str[i + 1] == '$')
			return (&str[i]);
		i++;
	}
	return (&str[i]);
}

char	*find_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?' || ft_isdigit(str[i + 1]))
				return (&str[i + 2]);
			if (str[i + 1] == '$')
				return (&str[i + 2]);
		}
		if (is_meta(str[i]))
			return (&str[i]);
		i++;
	}
	return (&str[i]);
}

char	*find_blank(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (is_space(str[index]))
			return (&str[index]);
		index++;
	}
	return (NULL);
}

char	*find_quotes(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			return (&str[index]);
		index++;
	}
	return (NULL);
}
