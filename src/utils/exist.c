/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:28:33 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/27 10:58:44 by dasimoes         ###   ########.fr       */
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
	else if (c == '(' || c == ')' || c == '~' || c == '-')
		return (1);
	else if (c == '*')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	else if (c == '(' || c == ')')
		return (1);
	return (0);
}
