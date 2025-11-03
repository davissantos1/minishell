/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:53:16 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/03 20:05:19 by dasimoes         ###   ########.fr       */
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

int	check_wildcard_str(char *input, char *match)
{
	if (match[0] == '.' && input[0] != '.')
		return (0);
	return (match_str(input, match));
}

int	dlen(char *dir)
{
	DIR		*stream;
	int		size;

	size = 0;
	if (!dir[0])
		dir = ".";
	stream = opendir(dir);
	while (readdir(stream))
		size++;
	closedir(stream);
	return (size);
}

char	*gdir(t_minishell *s, char *str)
{
	char	*path;
	char	*wild;

	wild = ft_strchr(str, '*');
	if (!(wild - str))
	{
		path = ft_strdup(".");
		if (!gc_addptr(path, s->gc, GC_TOKEN))
			exit_code(s, EXIT_FAILURE);
		return (path);
	}
	path = gc_calloc((wild - str + 1) * sizeof(char *), s->gc, GC_TOKEN);
	if (!path)
		exit_code(s, EXIT_FAILURE);
	path = ft_memcpy(path, str, wild - str);
	return (path);
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
	path = gc_calloc((wild - str + 1) * sizeof(char *), s->gc, GC_TOKEN);
	if (!path)
		exit_code(s, EXIT_FAILURE);
	path = ft_memcpy(path, str, wild - str);
	return (path);
}
