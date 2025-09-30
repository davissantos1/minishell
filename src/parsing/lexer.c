/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:32:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/30 19:49:57 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_quotes(t_minishell *s, int i)
{
	char	*next_single;
	char	*next_double;
	char	*str;

	str = NULL;
	next_single = ft_strchr(s->input + i + 1, '\'');	
	next_double = ft_strchr(s->input + i + 1, '\"');
	if ((!next_single && !next_double) || (next_single && next_double))
	{
		s->error = "syntax error: unexpected end of file\n";
		exit_code(s, 2);
	}
	else if (next_single)
		str = ft_substr(s->input, i, next_single - s->input - i);
	else
		str = ft_substr(s->input, i, next_double - s->input - i);
	if (!gc_addptr(str, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	return (str);
}

char	*token_special(t_minishell *s, int i)
{
	char	*token;

	token = NULL;
	if (s->input[i] == '(')
		token = ft_strdup("(");
	if (s->input[i] == ')')
		token = ft_strdup(")");
	if (s->input[i] == '>' && s->input[i + 1] == '>')
		token = ft_strdup(">>");
	if (s->input[i] == '>' && s->input[i + 1] != '>')
		token = ft_strdup(">");
	if (s->input[i] == '<' && s->input[i + 1] == '<')
		token = ft_strdup("<<");
	if (s->input[i] == '<' && s->input[i + 1] != '<')
		token = ft_strdup("<");
	if (s->input[i] == '|' && s->input[i + 1] == '|')
		token = ft_strdup("||");
	if (s->input[i] == '|' && s->input[i + 1] != '|')
		token = ft_strdup("|");
	if (s->input[i] == '&' && s->input[i + 1] == '&')
		token = ft_strdup("&&");
	if (!gc_addptr(token, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	return (token);
}

char	*token_word(t_minishell *s, int i)
{
	char	*token;
	int		j;

	j = i;
	token = NULL;
	while (1)
	{
		if (s->input[j] == '\0')
			break ;
		else if (s->input[j] == '\'' || s->input[j] == '\"')
			break ;
		else if (is_meta(s->input[j]))
			break ;
		else if (is_space(s->input[j]))
			break ;
		j++;
	}
	token = ft_substr(s->input, i, j - i);
	if (!gc_addptr(token, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
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
		if (s->input[index] == '\'' || s->input[index] == '\"')
			str = token_quotes(s, index);
		else if (is_meta(s->input[index]))
			str = token_special(s, index);
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
	token_add(s, NULL);
}
