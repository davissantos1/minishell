/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:02:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/07 10:45:35 by vitosant         ###   ########.fr       */
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
# include "redir.h"
# include "executor.h"

// Macros

// Enums
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIN,
	TOKEN_REDOUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOL,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_QUOTES,
	TOKEN_LPAREN,
	TOKEN_RPAREN
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
	struct s_token	*next;
	struct s_token	*prev;
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
	struct s_token	*head;
	struct s_ast	*root;
	struct s_lstpid	*lst_pid;
	char			**env;
	char			*input;
	char			*error;
	char			*path;
	int				signal;
	int				exit;
	int				std_in;
	int				std_out;
	int				std_err;
}	t_minishell;

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
int			shell_process(t_minishell *shell);
int			is_space(char c);
int			is_meta(char c);
void		exit_code(t_minishell *shell, int code);
void		token_print(t_minishell *s);
void		token_add(t_minishell *s, char *str);
int			token_type(char *token);
t_token		*token_create(t_minishell *s, char *str);
char		*token_quotes(t_minishell *s, int i);
char		*token_special(t_minishell *s, int i);
char		*token_word(t_minishell *s, int i);
void		lexer(t_minishell *s);

#endif
