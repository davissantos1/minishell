/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:35:01 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/01 16:12:27 by dasimoes         ###   ########.fr       */
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

// Globals
extern volatile sig_atomic_t g_signal;

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
	int				std_in;
	int				std_out;
	int				std_err;
}	t_minishell;

typedef struct s_cmd
{
	char		**argv;
	int			is_builtin;
	int			std_in;
	int			std_out;
	t_redir		*redir;
}	t_cmd;

typedef struct s_subshell
{
	char		*input;
	int			std_in;
	int			std_out;
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
# include "redir.h"
# include "executor.h"

t_minishell	*shell_init(char **env);
int			shell_process(t_minishell *shell, char *input);
int			shell_read(t_minishell *shell, char *input);
int			is_space(char c);
int			is_meta(char c);
int			is_operator(char c);
void		exit_code(t_minishell *shell, int code);
void		token_print(t_minishell *s);
void		token_add(t_minishell *s, char *str);
int			token_type(char *token);
t_token		*token_create(t_minishell *s, char *str);
void		lexer(t_minishell *s);
int			check_quotes(char *token);
int			word_size(char *token, char quotes);
char		*remove_quotes(t_minishell *s, char *t);
void		error_code(t_minishell *shell, int code);
void		parser(t_minishell *s);
char		*av_convert(t_minishell *s, char **av);
t_token		*parser_handler(t_token *s);
t_ast		*node_handler(t_minishell *s, t_token *start, t_token *end);
t_redir		*redirect_create(t_minishell *s);
void		redirect_add(t_minishell *s, t_cmd *cmd, t_token *token);
t_ast		*ast_create(t_minishell *s);
t_cmd		*cmd_create(t_minishell *s, int ac);
t_ast		*cmd_node(t_minishell *s, t_token *start, t_token *end);
t_ast		*subshell_node(t_minishell *s, t_token *start, t_token *end);
t_ast		*operator_node(t_minishell *s, t_token *token);
void		ast_print(t_ast *root);
t_subshell	*subshell_create(t_minishell *s);
int			node_type(int token_type);
int			redir_type(int token_type);
void		node_insert(t_ast **root, t_ast *node);
void		ast_flip(t_ast **root);
int			token_size(t_token *start, t_token *end);
int			count_single_quotes(char *str);
char		*get_env(char **env, char *var);
char		**expand_argv(t_minishell *s, char **av);
void		signal_interrupt(int sig);
void		signal_child(int sig);
void		register_parent_signals(void);
void		register_child_signals(void);
void		validate_terminal(t_minishell *s);
void		validate_single(t_minishell *s);
void		validate_duplicate(t_minishell *s);
void		token_validate(t_minishell *s);
char		*token_special(t_minishell *s, int i);
char		*token_word(t_minishell *s, int i);
char		*token_quotes(t_minishell *s, int i);
int			check_wildcard_char(char *str);
int			check_wildcard_str(char *str, char *match);
int			dir_len(char *dir);
char		*find_break(char *str);
char		*expand_tilde(t_minishell *s, char *var);
int			only_quotes(char *str, char quotes);
char		*find_blank(char *str);
int			expand_check(char *str);
char		*expand_special(t_minishell *s, char *var);
void		handle_wildcard(t_minishell *s, char ***result, int pos);
int			dollar_expand(char *str);
void		expand_redirect(t_minishell *s, t_redir *redir);
char		*find_quotes(char *str);
int			expand_check_quotes(char *str);

#endif
