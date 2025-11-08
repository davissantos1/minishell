/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:00:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/08 11:22:01 by dasimoes         ###   ########.fr       */
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
			if (token_check_range(b) > 0)
				if (token_check_range(a) > 0)
					s->error = a->value;
		}
		b = b->next;
	}
}

void	validate_single(t_minishell *s)
{
	t_token	*t;

	t = s->head;
	if (token_check_range(t) > 0)
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

void	validate_subshell(t_minishell *s)
{
	t_token		*cur;
	int			rparen;
	int			lparen;

	rparen = 0;
	lparen = 0;
	cur = s->head;
	while (cur)
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
		if (s->error)
			return ;
		cur = cur->next;
	}
	if (rparen - lparen)
		s->error = "syntax error: unexpected end of file";
}

void	validate_quotes(t_minishell *s)
{
	t_token	*cur;
	int		open;
	int		index;
	char	quotes;

	cur = s->head;
	while (cur)
	{
		index = -1;
		open = 0;
		while (cur->value && cur->value[++index])
		{
			if (cur->value[index] == '\'' || cur->value[index] == '\"')
			{
				if (!open)
				{
					open = 1;
					quotes = cur->value[index];
				}
				else if (cur->value[index] == quotes && open)
					open = 0;
			}
		}
		if (open)
			s->error = "<newline>";
		cur = cur->next;
	}
}
