/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:10:51 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/10 14:24:42 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redirect_create(t_minishell *s)
{	
	t_redir	*redirect;

	redirect = gc_calloc(sizeof(t_redir), s->gc, GC_CMD);
	if (!redirect)
		exit_code(s, EXIT_FAILURE);
	
	return (redirect);
}

void	redirect_add(t_minishell *s, t_cmd *cmd, t_token *token)
{
	t_redir *new;
	t_redir *tmp;

	tmp = cmd->redir;
	new = redirect_create(s);
	if (!cmd->redir)
	{
		cmd->redir = new;
		new->type = redir_type(token->type);
		new->file = (token->next)->value;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->type = redir_type(token->type);
		new->file = (token->next)->value;
		tmp->next = new;
		new->prev = tmp;
	}
}
	
