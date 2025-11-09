/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:03:29 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/09 20:05:36 by dasimoes         ###   ########.fr       */
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
			if (token_check_range(b) == 2)
			{
				if (token_check_range(a) == 2)
					s->error = a->value;
			}
			if (token_check_range(b) == 1)
			{
				if (token_check_range(a) > 0)
					s->error = a->value;
			}
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
					is_open(&open, &quotes, cur->value[index]);
				else if (cur->value[index] == quotes && open)
					open = 0;
			}
		}
		if (open)
			s->error = "<newline>";
		cur = cur->next;
	}
}

void	is_open(int *open, char *quotes, char index)
{
	*open = 1;
	*quotes = index;
}
