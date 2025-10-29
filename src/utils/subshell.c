/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:55:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/10 14:57:34 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_subshell	*subshell_create(t_minishell *s)
{
	t_subshell	*sub;

	sub = gc_calloc(sizeof(t_subshell), s->gc, GC_AST);
	if (!sub)
		exit_code(s, EXIT_FAILURE);
	return (sub);
}
