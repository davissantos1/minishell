/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:48:35 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/01 09:50:50 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_program(char **args, char **env, int std_in, int std_out);

void	executor(t_cmd *cmd)
{
	pid_t	fork_id;

	fork_id = fork();
	if (fork_id == -1)
		return (panic("fork"));
}

static void	exec_program(char **args, char **env, int std_in, int std_out)
{
	if (dup2(std_in, STDIN_FILENO) == -1)
		perror("");
	if (dup2(std_out, STDOUT_FILENO) == -1)
		perror("");
	if (close(std_in) == -1)
		perror("");
	if (close(std_out) == -1)
		perror("");
	execve(args[0], args, env);
	perror("");
	exit(errno);
}
