/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:02:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/11 16:36:26 by dasimoes         ###   ########.fr       */
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

// Enums
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIN,
	TOKEN_REDOUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
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
typedef struct s_redir
{
	t_redir_type	type;
	char			*file; // filename or delimiter
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd
{
	char		**argv;
	int			is_builtin;
	int			std_in;
	int			std_out;
	t_redir		*redir;
}	t_cmd;

typedef struct	s_subshell
{
	char		*input;
}	t_subshell;
	
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
int			shell_process(t_minishell *shell, char *input);
int			shell_read(t_minishell *shell, char *input);
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
int			check_quotes(char *token);
int			word_size(char *token);
char		*remove_quotes(t_gc *gc, char *token);
void		error_code(t_minishell *shell, int code);
void		parser(t_minishell *s);
char		*av_convert(t_minishell *s, char **av);
t_token		*parser_handler(t_token *s);
t_ast		*node_handler(t_minishell *s, t_token *start, t_token *end);
t_redir		*redirect_create(t_minishell *s);
void		redirect_add(t_minishell *s, t_cmd *cmd, t_token *token);
t_ast		*ast_create(t_minishell *s);
t_cmd		*cmd_create(t_minishell *s);
t_ast		*cmd_node(t_minishell *s, t_token *start, t_token *end);
t_ast		*subshell_node(t_minishell *s, t_token *start, t_token *end);
t_ast		*operator_node(t_minishell *s, t_token *token);
void		ast_print(t_ast *root);
t_subshell	*subshell_create(t_minishell *s);
int			node_type(int token_type);
int			redir_type(int token_type);
void		node_insert(t_ast *root, t_ast *node);

#endif
