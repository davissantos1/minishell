/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:45:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/11 18:54:19 by dasimoes         ###   ########.fr       */
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

char	*join_subshell(t_minishell *s, t_token *start)
{
	char		*join;
	char		*temp;

	join = ft_strdup("");
	start = start->next;
	while (start->type != TOKEN_RPAREN)
	{
		temp = join;
		join = ft_strjoin(temp, start->value);
		free(temp);
		temp = join;
		join = ft_strjoin(join, " ");
		free(temp);
		start = start->next;
	}
	if (!gc_addptr(join, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (join);
}

int	cvar(char *str)
{
	int	size;
	int	i;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '$')
				size++;
			else if (str[i + 1] && !is_space(str[i + 1]))
			{
				if (!is_meta(str[i + 1]))
					size++;
			}
			i++;
		}
	}
	return (size);
}

int	find_index(char *str, char *match)
{
	int	index;

	index = 0;
	while (*str)
	{
		if (str == match)
			return (index);
		index++;
		str++;
	}
	return (index);
}
