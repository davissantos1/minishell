/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:02:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/30 11:59:58 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// External includes
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

// Local includes
# include "libft.h"

// Macros
# define LEFT 1
# define RIGHT 0

// Enums
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_REDIR_APPEND,
	TOKEN_EOF,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_WILDCARD
}	t_token_type;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIN,
	NODE_REDOUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_AND,
	NODE_OR
}	t_node_type;

// Lexer and parser structs
typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	void			*data;
}	t_ast;

typedef struct s_minishell
{
	struct s_gc		*gc;
	struct s_list	*tokens;
	struct s_ast	*root;
	unsigned int	flags;
	char			**env;
	char			*input;
	int				signal;
	int				exit;
	int				std_in;
	int				std_out;
	int				std_err;
}	t_minishell;

typedef struct s_redir
{
	t_node_type		type;
	char			*file;
}	t_redir;

//Execution structs 
typedef struct s_cmd
{
	char		**argv;
	int			is_builtin;
	int			std_in;
	int			std_out;
	t_list		*redir;
}	t_cmd;

//typedef struct s_pipe
//{
//	// to be defined
//}	t_pipe;
//
//typedef struct s_logic
//{
//	// to be defined
//}	t_logic;

//Prototypes
t_minishell	*shell_init(char **env);
void		exit_code(t_minishell *shell, int code);

#endif
