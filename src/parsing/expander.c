/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/19 09:45:21 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_check(char **spl, int pos)
{
	char	*var;
	char	*dol;

	dol = spl + pos;
	var = spl + pos + 1;
	if (pos == 0 && var)
		return (1);
	else if (pos > 0 && var && !(var + 1))
		return (1);
	if (count_single_quotes(var + 1) % 2 != 0)
		if (count_single_quotes(dol - 1) % 2 != 0)
			return (0);
	if (count_double_quotes(var + 1) % 2 != 0)
		if (count_double_quotes(dol - 1) % 2 != 0)
			return (1);
	return (1);
}

static char	*expand_string(t_minishell *s, char *str)
{
	char	**spl;
	int		i;

	i = 0;
	spl = ft_split(str, '$');
	if (!gc_addmtx(spl, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	while (spl[i])
	{
		if (spl[i][0] == '$')
		{
			if (expand_check(spl, i))
			{
				spl[i + 1] = ft_strdup(get_env(s, spl[i + 1]));
				if (!gc_addptr(spl[i + 1], s->gc, GC_AST))
					exit_code(s, EXIT_FAILURE);
			}
		}
		i++;
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
