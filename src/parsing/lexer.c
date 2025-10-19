/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:32:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/19 08:49:00 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_special(t_minishell *s, int i)
{
	if (s->input[i] == '(')
		return ft_strdup("(");
	if (s->input[i] == ')')
		return ft_strdup(")");
	if (s->input[i] == '>' && s->input[i + 1] == '>')
		return ft_strdup(">>");
	if (s->input[i] == '>' && s->input[i + 1] != '>')
		return ft_strdup(">");
	if (s->input[i] == '<' && s->input[i + 1] == '<')
		return ft_strdup("<<");
	if (s->input[i] == '<' && s->input[i + 1] != '<')
		return ft_strdup("<");
	if (s->input[i] == '|' && s->input[i + 1] == '|')
		return ft_strdup("||");
	if (s->input[i] == '|' && s->input[i + 1] != '|')
		return ft_strdup("|");
	if (s->input[i] == '&' && s->input[i + 1] == '&')
		return ft_strdup("&&");
	if (s->input[i] == '&' && s->input[i + 1] != '&')
		s->error = s->input + i + 1;
	return (NULL);
}

static char	*token_word(t_minishell *s, int i)
{
	char	*token;
	int		j;

	j = i;
	token = NULL;
	while (1)
	{
		if (s->input[j] == '\0')
			break ;
		else if (is_meta(s->input[j]))
			break ;
		else if (is_space(s->input[j]))
			break ;
		j++;
	}
	token = ft_substr(s->input, i, j - i);
	if (!check_quotes(token))
		s->error = token + ft_strlen(token) - 1;
	return (token);
}

static char	*token_quotes(t_minishell *s, int i)
{
	char	*token;
	int		j;

	j = i + 1;
	token = NULL;
	while (1)
	{
		if (s->input[j] == '\0')
			break ;
		else if (s->input[j] == s->input[i])
			break ;
		j++;
	}
	token = ft_substr(s->input, i, j - i + 1);
	if (!check_quotes(token))
		s->error = token + ft_strlen(token) - 1;
	return (token);
	
}

void	lexer(t_minishell *s)
{
	char	*str;
	int		index;

	index = 0;
	while (s->input[index])
	{
		str = NULL;
		if (is_meta(s->input[index]))
			str = token_special(s, index);
		else if (s->input[index] == '\'' || s->input[index] == '\"')
			str = token_quotes(s, index);
		else if (!is_space(s->input[index]))
			str = token_word(s, index);
		if (str)
		{
			token_add(s, str);
			index += ft_strlen(str);
		}
		else
			index++;
	}
	if (s->head)
		token_add(s, NULL);
}
