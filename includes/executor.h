/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:52:51 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/21 16:00:30 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define STDIN_FD 1
# define STDOUT_FD 0
# define FORKED 0
# define NOT_FORKED 1

# include "minishell.h"

typedef struct s_lstpid
{
	char			is_builtin;
	int				rbuiltin;
	pid_t			pid;
	struct s_lstpid	*next;
}					t_lstpid;

typedef void (*func)(t_minishell *, t_cmd *);

void	executor(t_minishell *shell, t_ast *node);
void	pid_add(t_minishell *shell, pid_t pid, char is_builtin, int rbuiltin);
int		last_return(t_minishell *shell);
int		check_command(t_minishell *shell, t_cmd *cmd);
void	builtin(t_minishell *shell, t_cmd *cmd);
void	handler(t_minishell *shell);
void	build_path(t_minishell *shell);
void	find_path(t_minishell *shell, t_cmd *cmd);
void	close_fdlst(t_lstint *lst);
void	add_var(t_minishell *shell, char *ovar);

void	or_node(t_minishell *shell, t_ast *node);
void	pipe_node(t_minishell *shell, t_ast *node);
void	and_node(t_minishell *shell, t_ast *node);

void	export_builtin(t_minishell *shell, t_cmd *cmd);
void	pwd_builtin(t_minishell *shell, t_cmd *cmd);
void	unset_builtin(t_minishell *shell, t_cmd *cmd);
void	exit_builtin(t_minishell *shell, t_cmd *cmd);
void	env_builtin(t_minishell *shell, t_cmd *cmd);
void	echo_builtin(t_minishell *shell, t_cmd *cmd);
void	cd_builtin(t_minishell *shell, t_cmd *cmd);

#endif
