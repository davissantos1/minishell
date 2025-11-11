/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:00:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/11 09:24:42 by dasimoes         ###   ########.fr       */
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
	int			open;

	open = 0;
	cur = s->head;
	while (cur && !s->error)
	{
		if (cur->type == TOKEN_LPAREN)
		{
			if (cur->prev && token_check_range(cur->prev) < 2)
				s->error = cur->value;
			if (cur->next && cur->next->type == TOKEN_RPAREN)
				s->error = cur->next->value;
			open++;
		}
		if (cur->type == TOKEN_RPAREN)
		{
			if (cur->next && token_check_range(cur->next) == 0)
				s->error = cur->next->value;
			open--;
		}
		cur = cur->next;
	}
	if (open && !s->error)
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
			if (token_check_range(b) == 1 && b->type != TOKEN_HEREDOC)
			{
				if (a->type == TOKEN_WORD && ft_strchr(a->value, '*'))
					s->error = "ambiguous redirect";
			}
		}
		b = b->next;
	}
}
