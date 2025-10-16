/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:33:06 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 14:19:50 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_process(t_minishell *shell, t_subshell *sub, char **tmp);

void	subshell(t_minishell *shell, t_subshell *sub)
{
	char	*tmp[3];
	char	**argv;

	tmp[0] = shell->path;
	tmp[1] = sub->input;
	tmp[2] = NULL;
	argv = ft_mtxdup(tmp);
	if (!argv)
		exit_code(shell, errno);
	sub_redirection(shell, sub);
	fork_process(shell, sub, tmp);
}

static void	fork_process(t_minishell *shell, t_subshell *sub, char **argv)
{
	pid_t	pid;
	char	**env;

	env = shell->env;
	pid = fork();
	if (pid == -1)
		exit_code(shell, errno);
	pid_add(shell, pid, NOT_BUILTIN, NOT_BUILTIN);
	if (pid > 0)
		return ;
	if (sub->std_in != 0 && dup2(sub->std_in, STDIN_FILENO) == -1)
		perror("dup2");
	if (sub->std_out != 1 && dup2(sub->std_out, STDOUT_FILENO) == -1)
		perror("dup2");
	sub_close_redir(sub);
	gc_free_all(shell->gc);
	execve(argv[0], argv, env);
	perror("execve");
	ft_mtxfree(argv);
	exit(errno);
}
