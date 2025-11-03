/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:53:16 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/02 23:07:14 by dasimoes         ###   ########.fr       */
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

int	check_wildcard_str(t_minishell *s, char *str, char *match)
{
	char	*normalized;
	char	*found;
	int		size;
	int		i;
	int		j;

	i = -1;
	j = -1;
	size = wild_size(str);
	normalized = gc_calloc((size + 1) * sizeof(char *), s->gc, GC_TOKEN);
	if (!normalized)
		exit_code(s, EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] != '*')
			normalized[++j] = str[i];
	}
	found = ft_strnstr(match, normalized, ft_strlen(match)); 
	if (found && *(found + ft_strlen(found)) == '*')
		return (1);
	if (found && *(found + ft_strlen(found)) == '\0')
		return (1);
	return (0);
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
