/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:13:40 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/10 17:37:10 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*node_handler(t_minishell *s, t_token *start, t_token *end)
{
	t_ast *node;

	node = NULL;
	if (start->type == TOKEN_WORD || start->type == TOKEN_QUOTES)
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
	else
		node = operator_node(s, start);
	return (node);
}

t_token	*parser_handler(t_token *start)
{
	t_token	*end;

	end = start;
	if (start->type >= TOKEN_WORD && start->type <= TOKEN_HEREDOC)
	{
		while (end->next->type >= 0 && end->next->type <= 4)
			end = end->next;
	}
	else if (start->type == TOKEN_LPAREN)
	{
		while (end->type != TOKEN_RPAREN || end->type != TOKEN_EOL)
			end = end->next;
	}
	return (end);
}

void	parser(t_minishell *s)
{
	t_token	*start;
	t_token	*end;
	t_ast	*node;
	t_ast	*temp;

	temp = NULL;
	start = s->head;
	if (start->type == TOKEN_EOL)
		return ;
	while (start->value)
	{
		end = parser_handler(start);
		if (!temp)
		{
			temp = node_handler(s, start, end);
			start = end->next;
		}
		else
			temp = node;
		node = node_handler(s, start, end);
		temp->right = node;
		node->left = temp;
		if (!s->root)
			s->root = node;
		start = end->next;
	}
	token_print(s);
	ast_print(s->root);
}
