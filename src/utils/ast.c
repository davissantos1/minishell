/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:43:00 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/03 14:25:15 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_create(t_gc *gc, t_token *token)
{
	t_ast *node;

	node = gc_calloc(sizeof(t_ast), gc, GC_AST);
	if (!node)
		return (NULL);
	node->type = node_type(gc, token->type);
	return (node);
}
