/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:47:45 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/03 12:22:34 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		token_type(char *token)
{
	if (!token)
		return (TOKEN_EOL);
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (TOKEN_QUOTES);
	if (*token == '(')
		return (TOKEN_LPAREN);
	if (*token == ')')
		return (TOKEN_RPAREN);
	if (*token == '>' && *(token + 1) == '>')
		return (TOKEN_APPEND);
	if (*token == '>' && *(token + 1) != '>')
		return (TOKEN_REDIN);
	if (*token == '<' && *(token + 1) == '<')
		return (TOKEN_HEREDOC);
	if (*token == '<' && *(token + 1) != '<')
		return (TOKEN_REDOUT);
	if (*token == '|' && *(token + 1) == '|')
		return (TOKEN_OR);
	if (*token == '|' && *(token + 1) != '|')
		return (TOKEN_PIPE);
	if (*token == '&' && *(token + 1) == '&')
		return (TOKEN_AND);
	return (TOKEN_WORD);
}

int	node_type(int token_type)
{
	if (token_type == TOKEN_WORD)
		return (NODE_CMD);
	if (token_type == TOKEN_PIPE)
		return (NODE_PIPE);
	if (token_type == TOKEN_AND)
		return (NODE_AND);
	if (token_type == TOKEN_OR)
		return (NODE_OR);
	return (-1);
}

int	redir_type(int token_type)
{
	if (token_type == TOKEN_REDIN)
		return (REDIN);
	if (token_type == TOKEN_REDOUT)
		return (REDOUT);
	if (token_type == TOKEN_APPEND)
		return (APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (HEREDOC);
	return (-1);
}
