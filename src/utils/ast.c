/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:43:00 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/11 16:37:15 by dasimoes         ###   ########.fr       */
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
	while (start != end && start != end->next)
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
	while (start != end)
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

void	node_insert(t_ast *root, t_ast *node)
{
	t_ast *tmp;

	tmp = root;
	if (!tmp->left)
	{
		tmp->left = node;
		node->right = tmp;
		return ;
	}
	if (!tmp->right)
	{
		tmp->right = node;
		node->left = tmp;
		return ;
	}
	node_insert(root->left, node);
	node_insert(root->right, node);
}

//int	ast_validate(t_ast *root)
//{
//	
//
//}
