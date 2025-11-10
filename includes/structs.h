/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:17:16 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/08 16:19:51 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "enums.h"

// Lexer and parser structs
typedef struct s_token
{
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
	char			*value;
}	t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	void			*data;
}	t_ast;

//list pid and fds
typedef struct s_lstint
{
	int				value;
	struct s_lstint	*next;
}					t_lstint;

typedef struct s_minishell
{
	struct s_gc		*gc;
	struct s_token	*head;
	struct s_ast	*root;
	struct s_lstpid	*lst_pid;
	struct s_lstint	*lstfd;
	char			**paths;
	char			**env;
	char			**tmp_var;
	char			*name;
	char			*input;
	char			*error;
	char			*path;
	int				signal;
	int				exit;
}	t_minishell;

typedef struct s_cmd
{
	char		**argv;
	int			is_builtin;
	int			std_in;
	int			std_out;
	t_redir		*redir;
}	t_cmd;

#endif