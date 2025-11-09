/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:00:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/09 20:16:45 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_terminal(t_minishell *s)
{
	t_token	*start;
	t_token	*end;

	start = s->head;
	end = start;
	while (end->next->value)
		end = end->next;
	if (start->type == TOKEN_RPAREN || (start->type >= 10))
		s->error = &start->value[ft_strlen(start->value) - 1];
	if ((end->type > 0 && end->type < 5) || end->type > 8)
	{
		if (end->type > 0 && end->type < 5)
			s->error = "newline";
		else
			s->error = end->value;
	}
}

void	validate_subshell(t_minishell *s)
{
	t_token		*cur;
	int			rparen;
	int			lparen;

	rparen = 0;
	lparen = 0;
	cur = s->head;
	while (cur && !s->error)
	{
		if ((cur->type == TOKEN_LPAREN) || (cur->type == TOKEN_RPAREN))
		{
			if (cur->type == TOKEN_LPAREN)
			{
				if (cur->prev && token_check_range(cur->prev) < 2)
					s->error = cur->value;
				lparen++;
			}
			if (cur->type == TOKEN_RPAREN)
				rparen++;
		}
		cur = cur->next;
	}
	if ((rparen - lparen) && !s->error)
		s->error = "syntax error: unexpected end of file";
}

void	validate_wildcard(t_minishell *s)
{
	t_token	*b;
	t_token	*a;

	b = s->head;
	while (b)
	{
		a = b->next;
		if (a)
		{
			if (token_check_range(b) == 1)
			{
				if (a->type == TOKEN_WORD && ft_strchr(a->value, '*'))
					s->error = "ambiguous redirect";
			}
		}
		b = b->next;
	}
	

}
