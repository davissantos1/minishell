/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/16 18:55:14 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_string(t_minishell *s, char *str)
{
	char	*expanded;

	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
	{
		
	}
	else
	{
		
	}

	return ()
}

char	**expand_argv(t_minishell *s, char **argv)
{
	char	**result;
	char	*dollar;
	int		index;

	index = 0;
	result = ft_calloc(sizeof(char *) * (ft_mtxlen(argv) + 1));
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (argv[index])
	{
		dollar = ft_strchr(argv[index], '$');
		if (!dollar)	
			result[index] = ft_strdup(av[index]);
		else
			result[index] = expand_string(av[index]);
		index++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (result);
}
