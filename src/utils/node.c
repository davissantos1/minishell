/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:26:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/06 18:56:43 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*cmd_node(t_minishell *s, t_token *start, t_token *end)
{
	int		index;
	t_ast	*node;
	t_cmd	*cmd;

	index = 0;
	node = ast_create(s);
	node->type = NODE_CMD;
	cmd = cmd_create(s, token_size(start, end));
	while (start != end->next)
	{
		if (start->type == 0 || (start->type >= 5 && start->type <= 7))
		{
			cmd->argv[index] = start->value;
			index++;
		}
		else if (start->type > 0 && start->type < 5)
		{
			redirect_add(s, cmd, start);
			if (start->next->value)
				start = start->next;
		}
		start = start->next;
	}
	node->data = cmd;
	return (node);
}

t_ast	*subshell_node(t_minishell *s, t_token *start, t_token *end)
{
	t_ast	*node;
	t_cmd	*cmd;

	node = ast_create(s);
	node->type = NODE_SUBSHELL;
	cmd = cmd_create(s, 3);
	cmd->argv[0] = s->path;
	while (start != end->next)
	{
		if (start->type == TOKEN_LPAREN)
		{
			cmd->argv[1] = join_subshell(s, start);
			while (start->type != TOKEN_RPAREN)
				start = start->next;
		}
		else if (start->type > 0 && start->type < 5)
		{
			redirect_add(s, cmd, start);
			if (start->next->value)
				start = start->next;
		}
		start = start->next;
	}
	node->data = cmd;
	return (node);
}

t_ast	*operator_node(t_minishell *s, t_token *token)
{
	t_ast	*node;

	node = ast_create(s);
	node->type = node_type(token->type);
	node->data = NULL;
	return (node);
}

void	node_insert(t_ast **root, t_ast *node)
{
	t_ast	*tmp;

	tmp = *root;
	if (!tmp->left)
	{
		tmp->left = node;
		ast_flip(root);
		return ;
	}
	if (!tmp->right)
	{
		tmp->right = node;
		return ;
	}
	node_insert(&(*root)->right, node);
}
