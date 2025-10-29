/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:45:28 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/29 20:10:41 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_special_aux(t_minishell *s, int i)
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
		s->error = "&";
	return (NULL);
}

char	*token_special(t_minishell *s, int i)
{
	if (s->input[i] == '*')
		return (token_word(s, i));
	if (s->input[i] == '~')
		return (token_word(s, i));
	if (s->input[i] == '$')
	{
		if (s->input[i + 1] == '$')
			if (is_space(s->input[i + 2]))
				return (ft_strdup("$$"));
		return (token_word(s, i));
	}
	if (s->input[i] == '-')
		return (token_word(s, i));
	return (token_special_aux(s, i));
}

char	*token_word(t_minishell *s, int i)
{
	char	*token;
	int		j;

	j = i + 1;
	token = NULL;
	while (1)
	{
		if (s->input[j] == '\0')
			break ;
		else if (is_operator(s->input[j]))
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

char	*token_quotes(t_minishell *s, int i)
{
	char	*token;
	int		closed;
	int		j;

	closed = 0;
	j = i + 1;
	token = NULL;
	while (1)
	{
		if (s->input[j] == '\0')
			break ;
		else if ((s->input[j] == '\'' || s->input[j] == '\"') && closed)
			closed = 0;
		else if ((s->input[j] == '\'' || s->input[j] == '\"') && !closed)
			closed = 1;
		else if (is_space(s->input[j]) && closed)
			break ;
		j++;
	}
	token = ft_substr(s->input, i, j - i + 1);
	if (!check_quotes(token))
		s->error = token + ft_strlen(token) - 1;
	return (token);
	
}
