/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/19 19:55:35 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_check(char **spl, int pos)
{
	if (pos == 0 || !spl[pos + 1])
		return (1);
	if (count_single_quotes(*spl - 1) % 2 != 0)
		if (count_single_quotes(*spl + 1) % 2 != 0)
			return (0);
	return (1);
}

static char	*expand_string_aux(t_minishell *s, char **spl, int i, int cd)
{
	char *res;

	res = NULL;
	if (expand_check(spl, i))
	{
		if (!ft_strncmp(spl[i], "~", 2))
			res = ft_strdup(get_env(s, "HOME"));
		else if (!ft_strncmp(spl[i], "?", 2))
			res = ft_itoa(s->exit + s->signal);
		else if (cd && !ft_strncmp(spl[i], "-", 2))
			res = ft_strdup(get_env(s, "OLDPWD"));
		else
			res = ft_strdup(get_env(s, spl[i]));
		if (!gc_addptr(res, s->gc, GC_AST))
			exit_code(s, EXIT_FAILURE);
	}
	return (res);
}

static char	*expand_string(t_minishell *s, char *str, int cd)
{
	char	**spl;
	char	*res;
	int		i;

	i = 0;
	if (str[0] != '$' && str[2])
		i = 1;
	spl = ft_split(str, '$');
	if (!gc_addmtx(spl, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	while (spl[i])
	{
		spl[i] = expand_string_aux(s, spl, i, cd);
		i++;
	}
	res = ft_reverse_split(spl, ' ');
	if (!gc_addptr(res, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (res);
}

char	**expand_argv(t_minishell *s, char **av)
{
	char	**result;
	char	*dollar;
	int		index;

	index = 0;
	result = ft_calloc(sizeof(char *), (ft_mtxlen(av) + 1));
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (av[index])
	{
		dollar = ft_strchr(av[index], '$');
		if (!dollar && ft_strcmp(av[index], "~") && ft_strcmp(av[index], "-"))
			result[index] = ft_strdup(av[index]);
		else if (index > 0 && !ft_strcmp(av[0], "cd"))
			result[index] = expand_string(s, av[index], 1);
		else
			result[index] = expand_string(s, av[index], 1);
		index++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (result);
}
