/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:32:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/01 17:57:27 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_special(t_minishell *s, int i)
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
	{
		s->error = "syntax error unexpected token `&'\n";
		exit_code(s, 2);
	}
	return (NULL);
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
		else if (is_meta(s->input[j]))
			break ;
		else if (is_space(s->input[j]))
			break ;
		j++;
	}
	token = ft_substr(s->input, i, j - i);
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

