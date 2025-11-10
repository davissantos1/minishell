/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:32:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/10 11:43:40 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_minishell *s)
{
	char	*str;
	int		index;

	index = 0;
	while (s->input && s->input[index])
	{
		str = NULL;
		if (is_meta(s->input[index]))
			str = token_special(s, index);
		else if (s->input[index] == '\'' || s->input[index] == '\"')
			str = token_quotes(s, index);
		else if (!is_space(s->input[index]))
			str = token_word(s, index);
		if (str)
		{
			token_add(s, str);
			index += ft_strlen(str);
		}
		else
			index++;
	}
	if (s->head)
		token_add(s, NULL);
}
