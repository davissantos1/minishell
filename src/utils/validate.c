/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:00:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/20 17:32:05 by dasimoes         ###   ########.fr       */
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
			if (start->type > 4 && after->type > 4)
			{
				s->error = &start->value[ft_strlen(start->value)];
				error_code(s, 2);
			}
		}
		start = start->next;
	}
}

void	validate_single(t_minishell *s)
{
	t_token *token;
	
	token = s->head;
	if (token-type > 2)
	{
		s->error = &start->value[ft_strlen(start->value)];
		error_code(s, 2);
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
	if (start->type == TOKEN_RPAREN || start->type > 9)
	{
		s->error = &start->value[ft_strlen(start->value)];
		error_code(s, 2);
	}
	if (end->type == TOKEN_LPAREN || end->type > 6)
	{
		s->error = &start->value[ft_strlen(start->value)];
		error_code(s, 2);
	}
}
