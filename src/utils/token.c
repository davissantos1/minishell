/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:42:28 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/30 17:45:57 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		token_type(char *token)
{
	if (!*token)
		return (TOKEN_EOL);
	if (*token == '\'')
		return (TOKEN_SQUOTE);
	if (*token == '\"')
		return (TOKEN_DQUOTE);
	if (*token == '(')
		return (TOKEN_LPAREN);
	if (*token == ')')
		return (TOKEN_RPAREN);
	if (*token == '>' && *(token + 1) == '>')
		return (TOKEN_APPEND);
	if (*token == '>' && *(token + 1) != '>')
		return (TOKEN_REDIN);
	if (*token == '<' && *(token + 1) == '<')
		return (TOKEN_HEREDOC);
	if (*token == '<' && *(token + 1) != '<')
		return (TOKEN_REDOUT);
	if (*token == '|' && *(token + 1) == '|')
		return (TOKEN_OR);
	if (*token == '|' && *(token + 1) != '|')
		return (TOKEN_PIPE);
	if (*token == '&' && *(token + 1) == '&')
		return (TOKEN_AND);
	return (TOKEN_WORD);
}

t_token	*token_create(t_minishell *s, char *str)
{
	t_token	*token;

	token = gc_calloc(sizeof(t_token), s->gc, GC_TOKEN);
	if (!token)
		exit_code(s, EXIT_FAILURE);
	token->type = token_type(str);
	token->value = str;
	return (token);
}

void	token_add(t_minishell *s, char *str)
{
	t_token *token;
	t_token *last;
	
	token = token_create(s, str);
	if (!s->head)
		s->head = token;
	else
	{
		last = s->head;
		while (last->next != NULL)
			last = last->next;
		last->next = token;
		token->prev = last;
	}
}

void	token_print(t_minishell *s)
{
	t_token	*token;
	int		count;

	count = 0;
	token = s->head;
	while (token->next != NULL)
	{
		printf("Token print: \n");
		printf("Number: %d\n", count);
		printf("type: %d\n", token->type);
		printf("Value: %s\n", token->value);
		token = token->next;
	}
}
