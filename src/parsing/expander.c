/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/25 19:44:29 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_check(char *str)
{
	int	quotes;
	int	index;

	index = 0;
	quotes = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			quotes++;
		if (str[index] == '$')
			break ;
		index++;
	}
	if (quotes % 2 != 0)
		return (0);
	return (1);
}

static char	*expand_var(t_minishell *s, char *var)
{
	char	*env_var;

	if (expand_check(var))
	{
		env_var = remove_quotes(s->gc, var);
		env_var = get_env(s, var + 1);
		if (!env_var)
			return (ft_strdup(""));
		return (ft_strdup(env_var));
	}
	return (var);
}

static char	*expand_quotes(t_minishell *s, char *str)
{
	char	**spl;
	char	*res;
	int	i;

	i = 0;
	spl = ft_split(str, '\"');
	if (!gc_addmtx(spl, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	while (spl[i])
	{
		if (ft_strchr(spl[i], '$'))
			spl[i] = expand_var(s, spl[i]);
		i++;
	}
	res = ft_reverse_split(spl, ' ');
	if (!gc_addptr(res, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	res = remove_quotes(s->gc, res);
	return (res);
}

void	check_wildcard(t_minishell *s, char ***result)
{
	int		index;
	char	**res;

	res = *result;
	index = 0;
	while (res[index])
	{
		if (res[index][0] == '*' && !res[index][1])
			expand_wildcard(s, result);
		index++;
	}
	res = ft_reverse_split(spl, ' ');
	res[ft_strlen(res) - 1] = '\0';
	return (res);
}

void	expand_wildcard(t_minishell *s, char ***av, int index)
{
	int				len;
	int				flow;
	DIR *			dir;
	struct dirent	*cur;

	flow = check_wildcard((*av)[index]);
	len = ft_strlen((*av)[index]);
	dir = opendir(".");
	if (!dir)
		return ;
	cur = readdir(dir);
	while (cur)
	{
		if (flow)
			(*av)[index] = ft_strdup(cur->d_name);
		else
		{
			if (check_wildcard_str(((*av)[index]), cur->d_name))
				(*av)[index] = ft_strdup(cur->d_name);

		}
		index++;
		cur = readdir(dir);
	}
}

char	**expand_argv(t_minishell *s, char **av)
{
	char	**result;
	int		index;

	index = 0;
	result = ft_calloc(sizeof(char *), (ft_mtxlen(av) + 1));
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (av[index])
	{	
		if (ft_strchr(av[index], '\"') || ft_strchr(av[index], '\''))
			result[index] = expand_quotes(s, av[index]);
		else if (av[index][0] == '$' && av[index][1])
			result[index] = expand_var(s, av[index]);
		else if (av[index][0] == '~' && !av[index][1])
			result[index] = getenv("HOME");
		index++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	check_wildcard(s, &result);
	return (result);
}
