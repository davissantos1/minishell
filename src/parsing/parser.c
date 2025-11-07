/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:13:40 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/07 17:40:46 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*node_handler(t_minishell *s, t_token *start, t_token *end)
{
	t_ast *node;

	if (start->type >= TOKEN_WORD && start->type <= TOKEN_VAR)
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
	if (start->type >= TOKEN_WORD && start->type <= TOKEN_VAR)
	{
		while (end->next->type >= 0 && end->next->type <= 7)
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
	t_token	*end;

	if (!s->head)
		return ;
	end = s->head;
	while (end->type != TOKEN_EOL)
		end = end->next;
	s->root = parse_logic(s, s->head, end);
}
