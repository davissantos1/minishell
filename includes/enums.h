/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:17:13 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/08 16:20:54 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

// Enums
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIN,
	TOKEN_REDOUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SQUOTES,
	TOKEN_DQUOTES,
	TOKEN_VAR,
	TOKEN_RPAREN,
	TOKEN_LPAREN,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOL,
}	t_token_type;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

typedef enum e_redir_type
{
	REDIN,
	REDOUT,
	APPEND,
	HEREDOC,
}	t_redir_type;

#endif
