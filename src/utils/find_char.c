/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:31:06 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/02 12:13:43 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_break(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '?' || ft_isdigit(str[i]) || str[i] == '$')
			return (&str[i + 1]);
		if (is_meta(str[i]))
			return (&str[i]);
		i++;
	}
	return (NULL);
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
	int index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			return (&str[index]);
		index++;
	}
	return (NULL);
}
