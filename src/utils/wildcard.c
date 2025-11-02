/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:53:16 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/02 12:27:46 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_wildcard_char(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] != '*')
			return (0);
		index++;
	}
	return (1);
}

int	check_wildcard_str(char *str, char *match)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) != ft_strlen(match))
		return (0);
	while (str[index])
	{
		if (str[index] == '*')
			index++;
		else
		{
			if (str[index] != match[index])
				return (0);
			index++;
		}
	}
	return (1);
}

int	dir_len(char *dir)
{
	int	size;
	DIR	*stream;

	size = 0;
	stream = opendir(dir);
	while (readdir(stream))
		size++;
	closedir(stream);
	return (size);
}

char	*get_wildcard_path(t_minishell *s, char *str)
{
	char	*path;
	char	*wild;

	wild = ft_strchr(str, '*');
	if (!(wild - str))
	{
		path = ft_strdup("");
		if (!gc_addptr(path, s->gc, GC_TOKEN))
			exit_code(s, EXIT_FAILURE);
		return (path);
	}
	path = gc_calloc((wild - str) * sizeof(char *), s->gc, GC_TOKEN);
	if (!path)
		exit_code(s, EXIT_FAILURE);
	path = ft_memcpy(path, str, wild - str - 1);
	return (path);
}
