/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:13:40 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/16 13:36:19 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*node_handler(t_minishell *s, t_token *start, t_token *end)
{
	t_ast *node;

	if (start->type >= TOKEN_WORD && start->type <= TOKEN_QUOTES)
		node = cmd_node(s, start, end);
	else if (start->type == TOKEN_LPAREN)
	{
		if (end->type != TOKEN_RPAREN)
		{
			s->error = "<newline>";
			error_code(s, 2);
			return (NULL);
		}
		node = subshell_node(s, start, end);
	}
	else if (start->type == TOKEN_EOL || start->type == TOKEN_RPAREN)
		node = NULL;
	else
		node = operator_node(s, start);
	return (node);
}

t_token	*parser_handler(t_token *start)
{
	t_token	*end;

	end = start;
	if (start->type >= TOKEN_WORD && start->type <= TOKEN_QUOTES)
	{
		while (end->next->type >= 0 && end->next->type <= 5)
			end = end->next;
	}
	else if (start->type == TOKEN_LPAREN)
	{
		while (end->type != TOKEN_RPAREN && end->type != TOKEN_EOL)
			end = end->next;
	}
	return (end);
}

void	parser(t_minishell *s)
{
	t_token	*start;
	t_token	*end;
	t_ast	*node;

	if (!s->head)
		return ;
	start = s->head;
	end = parser_handler(start);
	s->root = node_handler(s, start, end);
	start = end->next;
	while (start->value)
	{
		end = parser_handler(start);
		node = node_handler(s, start, end);
		node_insert(&s->root, node);
		start = end->next;
	}
	//if (!ast_validate(s->root))
	//{
	//	error_code(s, 2)
	//	s->root = NULL;
	//}
}
