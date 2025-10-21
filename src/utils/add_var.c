/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:59:37 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/21 16:00:06 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(t_minishell *shell, char *ovar)
{
	char	*var;
	char	*exists;
	char	*equal;

	var = ft_strdup(ovar);
	if (!var || !gc_addptr(var, shell->gc, GC_LOCALVARS))
		exit_code(shell, errno);
	equal = ft_strchr(ovar, '=');
	*equal = '\0';
	exists = get_env(shell, ovar);
	if (exists)
	{
		exists = exists - ft_strlen(ovar) - 2;
		shell->env = ft_mtxdel(shell->env, exists);
		if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
	}
	shell->env = ft_mtxadd(shell->env, var);
	if (!shell->env || !gc_addptr(shell->env, shell->gc, GC_LOCALVARS))
			exit_code(shell, errno);
}
