/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:52:35 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/11 13:04:27 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_dollar(char cur, char next, int squote, int dquote)
{
	if (cur == '$' && next)
	{
		if ((!dquote && !squote) || dquote > squote)
		{
			if (ft_isalnum(next) || next == '_')
				return (1);
			if (next == '?' || next == '$')
				return (1);
		}
	}
	return (0);
}

int	maybe_expand(char *str)
{
	int		squote;
	int		dquote;
	int		i;

	i = -1;
	squote = 0;
	dquote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !squote)
			squote++;
		else if (str[i] == '\'' && squote)
			squote--;
		else if (str[i] == '\"' && !dquote)
			dquote += 2;
		else if (str[i] == '\"' && dquote)
			dquote -= 2;
		if (check_dollar(str[i], str[i + 1], squote, dquote))
			return (1);
	}
	return (0);
}
