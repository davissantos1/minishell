/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:00:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/26 10:41:54 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_duplicate(t_minishell *s)
{
	t_token	*b;
	t_token	*a;

	b = s->head;
	while (b)
	{
		a = b->next;
		if (a)
		{
			if (b->type != 0 && b->type > 7 && b->type < 5 && b->type != 13)
				if (a->type != 0 && a->type > 7 && a->type < 5 && a->type != 13)
					s->error = b->value;
		}
		b = b->next;
	}
}

void	validate_single(t_minishell *s)
{
	t_token *t;
	
	t = s->head;
	if (t->type != 0 && t->type > 7 && t->type < 5 && t->type != 13)
	{
		if (t->type > 0 && t->type < 5)
			s->error = "newline";
		else
			s->error = t->value;
	}
}

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
