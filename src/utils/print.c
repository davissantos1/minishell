/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:31:08 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/12 18:41:14 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_print(t_ast *root)
{
	if (!root)
		return ;
	
	ast_print(root->left);
	printf("\nAST PRINT:\n");
	if (root->type == NODE_CMD)
		printf("CMD NODE");
	if (root->type == NODE_PIPE)
		printf("PIPE NODE");
	if (root->type == NODE_AND)
		printf("AND NODE");
	if (root->type == NODE_OR)
		printf("OR NODE");
	if (root->type == NODE_SUBSHELL)
		printf("SUBSHELL NODE");
	printf("\nNode type code: %d\n", root->type);
	ast_print(root->right);
	return ;
}

void	token_print(t_minishell *s)
{
	t_token	*token;
	int		count;

	count = 0;
	token = s->head;
	while (token)
	{
		printf("\n--------------\n");
		printf("Token print: \n");
		printf("Number: %d\n", count);
		printf("type: %d\n", token->type);
		printf("Value: %s\n", token->value);
		token = token->next;
		count++;
	}
}
