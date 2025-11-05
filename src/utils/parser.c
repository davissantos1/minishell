/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:21:47 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/05 17:03:26 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_logic(t_minishell *s, t_token *start, t_token *end)
{
	t_ast	*node;
	t_token	*cur;

	cur = end;
	while (cur != start)
	{
		if (cur->type == TOKEN_AND || cur->type == TOKEN_OR)
		{
			node = node_handler(s, cur, cur);
			node->left = parse_logic(s, start, cur->prev);
			node->right = parse_pipe(s, cur->next, end);
			return (node);
		}
		cur = cur->prev;
	}
	return (parse_pipe(s, start, end));
}

t_ast	*parse_pipe(t_minishell *s, t_token *start, t_token *end)
{
	t_ast	*node;
	t_token	*cur;

	cur = end;
	while (cur != start)
	{
		if (cur->type == TOKEN_PIPE)
		{
			node = node_handler(s, cur, cur);
			node->left = parse_pipe(s, start, cur->prev);
			node->right = parse_command(s, cur->next, end);
			return (node);
		}
		cur = cur->prev;
	}
	return (parse_command(s, start, end));
}

t_ast	*parse_command(t_minishell *s, t_token *start, t_token *end)
{
	t_ast	*node;

	node = node_handler(s, start, end);
	return (node);
}
