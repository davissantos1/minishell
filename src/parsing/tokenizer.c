/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:45:28 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/10 21:11:53 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_special_aux(t_minishell *s, int i)
{
	if (s->input[i] == '(')
		return (ft_strdup("("));
	if (s->input[i] == ')')
		return (ft_strdup(")"));
	if (s->input[i] == '>' && s->input[i + 1] == '>')
		return (ft_strdup(">>"));
	if (s->input[i] == '>' && s->input[i + 1] != '>')
		return (ft_strdup(">"));
	if (s->input[i] == '<' && s->input[i + 1] == '<')
		return (ft_strdup("<<"));
	if (s->input[i] == '<' && s->input[i + 1] != '<')
		return (ft_strdup("<"));
	if (s->input[i] == '|' && s->input[i + 1] == '|')
		return (ft_strdup("||"));
	if (s->input[i] == '|' && s->input[i + 1] != '|')
		return (ft_strdup("|"));
	if (s->input[i] == '&' && s->input[i + 1] == '&')
		return (ft_strdup("&&"));
	if (s->input[i] == '&' && s->input[i + 1] != '&')
		s->error = "&";
	return (NULL);
}

char	*token_special(t_minishell *s, int i)
{
	if (is_operator(s->input[i]))
		return (token_special_aux(s, i));
	if (s->input[i] == '(' || s->input[i] == ')')
		return (token_special_aux(s, i));
	if (s->input[i] == '$')
	{
		if (s->input[i + 1] == '$')
			if (is_space(s->input[i + 2]))
				return (ft_strdup("$$"));
		return (token_word(s, i));
	}
	return (token_word(s, i));
}

char	*token_word(t_minishell *s, int i)
{
	char	quotes;
	int		open;
	int		j;

	j = i + 1;
	open = 0;
	while (1)
	{
		if (is_operator(s->input[j]))
			break ;
		else if ((s->input[j] == '\'' || s->input[j] == '\"') && !open)
			is_open(&open, &quotes, s->input[j]);
		else if (open && s->input[j] == quotes)
			open = 0;
		else if (is_space(s->input[j]) && !open)
			break ;
		if (s->input[j] == ')')
			break ;
		j++;
	}
	return (ft_substr(s->input, i, j - i));
}

char	*token_quotes(t_minishell *s, int i)
{
	char	*token;
	int		closed;
	int		j;

	closed = 0;
	j = i + 1;
	while (1)
	{
		if (s->input[j] && s->input[j] == s->input[i] && closed)
			closed = 0;
		else if (s->input[j] && s->input[j] == s->input[i] && !closed)
			closed = 1;
		else if ((is_space(s->input[j]) || is_operator(s->input[j])) && closed)
			break ;
		else if (is_operator(s->input[j]) && closed)
			break ;
		else if (s->input[j] == '\0')
			break ;
		j++;
	}
	token = ft_substr(s->input, i, j - i);
	return (token);
}
