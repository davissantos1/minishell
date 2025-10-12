/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:31:08 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/12 12:40:05 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_print(t_ast *root)
{
	if (!root)
		return ;
	
	ast_print(root->left);
	printf("AST PRINT:\n");
	printf("node type: %d\n", root->type);
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
