/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:38:30 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/25 15:39:06 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_validate(t_minishell *s)
{
	if (!s->head)
		return ;
	if (s->head->type == TOKEN_EOL)
		return ;
	if (!s->head->next->value)
	{
		validate_single(s);
		return ;
	}
	validate_duplicate(s);
	validate_terminal(s);
}
