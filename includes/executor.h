/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:52:51 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/11 12:12:05 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define NODE_SUBSHELL 919
# define STDIN_FD 1
# define STDOUT_FD 0
# define NOT_BUILTIN 0
# define IS_BUILTIN 1

# include "minishell.h"

typedef struct	s_lstpid
{
	char			is_builtin;
	int				rbuiltin;
	pid_t			pid;
	struct s_lstpid	*next;
}					t_lstpid;

void	executor(t_minishell *shell, t_ast *node);
void	close_pipes(int	*pipe_fd);
void 	pid_add(t_minishell *shell, pid_t pid, char is_builtin, int rbuiltin);
int		get_return(t_minishell *shell);
int		check_command(t_cmd *cmd);
void	builtin(t_minishell *shell, t_cmd *cmd);

void	or_node(t_minishell *shell, t_ast *node);
void	pipe_node(t_minishell *shell, t_ast *node);
void	and_node(t_minishell *shell, t_ast *node);

#endif
