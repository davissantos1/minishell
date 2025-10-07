/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:52:51 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/07 12:05:07 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define NODE_SUBSHELL 919
# define STDIN_FD 1
# define STDOUT_FD 0

typedef struct	s_lstpid
{
	pid_t			pid;
	struct s_lstpid	*next;
}					t_lstpid;

void	executor(t_minishell *shell, t_ast *node);
void	close_pipes(int	*pipe_fd);
void 	pid_add(t_minishell *shell, pid_t pid);
int		get_return(t_minishell *shell);
int		check_command(t_cmd *node);
#endif
