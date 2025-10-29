/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:00:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/21 09:40:47 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' )
		return (1);
	else if (c == '\n' || c == '\r' || c == '\v')
		return (1);
	else
		return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	else if (c == '(' || c == ')')
		return (1);
	return (0);
}

void	validate_duplicate(t_minishell *s)
{
	t_token	*start;
	t_token	*after;

	start = s->head;
	while (start)
	{
		after = start->next;
		if (after)
		{
			if (start->type != 0 && start->type != 12 && start->type != 5)
				if (after->type != 0 && after->type != 12 && after->type != 5)
					s->error = start->value;
		}
		start = start->next;
	}
}

void	validate_single(t_minishell *s)
{
	t_token	*token;

	token = s->head;
	if (token->type != 0 && token->type != 12 && token->type != 5)
	{
		if (token->type > 0 && token->type < 5)
			s->error = "newline";
		else
			s->error = token->value;
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
	if (start->type == TOKEN_RPAREN || start->type >= 9)
		s->error = &start->value[ft_strlen(start->value) - 1];
	if ((end->type > 0 && end->type < 5) || end->type > 6)
	{
		if (end->type > 0 && end->type < 5)
			s->error = "newline";
		else
			s->error = end->value;
	}
}
