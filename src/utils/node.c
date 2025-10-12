/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:26:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/12 18:25:33 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*cmd_node(t_minishell *s, t_token *start, t_token *end)
{
	int		index;
	t_ast	*node;
	t_cmd	*cmd;

	index = 0;
	cmd = cmd_create(s);
	node = ast_create(s);
	node->type = NODE_CMD;
	while (start != end->next)
	{
		if (start->type == TOKEN_WORD || start->type == TOKEN_QUOTES)
		{
			cmd->argv[index] = start->value;
			index++;
		}
		else
		{
			redirect_add(s, cmd, start);
			start = start->next;
		}
		start = start->next;
	}
	node->data = cmd;
	return (node);
}

t_ast	*subshell_node(t_minishell *s, t_token *start, t_token *end)
{
	char		*join;
	char		*temp;
	t_ast		*node;
	t_subshell	*sub;

	join = NULL;
	node = ast_create(s);
	sub = subshell_create(s);
	node->type = NODE_SUBSHELL;
	start = start->next;
	while (start != end->next)
	{
		temp = join;
		join = ft_strjoin(temp, start->value);
		free(temp);
		start = start->next;
	}
	if (!gc_addptr(join, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	sub->input = join;
	node->data = sub;
	return (node);
}

t_ast	*operator_node(t_minishell *s, t_token *token)
{
	t_ast *node;

	node = ast_create(s);
	node->type = node_type(token->type);
	node->data = NULL;
	return (node);
}

void	node_insert(t_ast **root, t_ast *node)
{
	t_ast *tmp;

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
