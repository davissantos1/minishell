/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:48:35 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/10 20:19:06 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_exec(t_minishell *shell, t_cmd *cmd);
static void	exec_program(t_minishell *shell, t_cmd *cmd);
static void	which_builtin(t_cmd *cmd);

void	executor(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
		try_exec(shell, node->data);
	else if (node->type == NODE_AND)
		and_node(shell, node);
	else if (node->type == NODE_OR)
		or_node(shell, node);
	else if (node->type == NODE_PIPE)
		pipe_node(shell, node);
}

static void	try_exec(t_minishell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		ret;

	ret = 1;
	if (*cmd->argv && ft_strcmp(cmd->argv[0], shell->path))
		cmd->argv = expand_argv(shell, cmd->argv);
	expand_redirect(shell, cmd->redir);
	while (cmd->argv[0] && cmd->argv[0][0] == '\0')
		cmd->argv++;
	redirection(shell, cmd);
	which_builtin(cmd);
	find_path(shell, cmd);
	if (cmd->std_in < 0 || cmd->std_out < 0 || !check_command(cmd, &ret))
		return (pid_add(shell, NOT_FORKED, NOT_FORKED, ret << 8));
	if (!cmd->argv[0])
		return (pid_add(shell, NOT_FORKED, NOT_FORKED, 0));
	if (cmd->is_builtin >= 0)
		return (builtin(shell, cmd));
	pid = fork();
	if (pid == -1)
		exit_code(shell, errno);
	if (pid == 0)
		exec_program(shell, cmd);
	pid_add(shell, pid, FORKED, FORKED);
	close_redir(shell, cmd);
}

static void	exec_program(t_minishell *shell, t_cmd *cmd)
{
	char		**argv;
	char		**env;

	register_child_signals();
	argv = cmd->argv;
	if (!argv)
	{
		gc_free_all(shell->gc);
		exit(0);
	}
	env = shell->env;
	if (!argv)
		exit_code(shell, errno);
	if (cmd->std_in != 0 && dup2(cmd->std_in, STDIN_FILENO) == -1)
		perror("dup2");
	if (cmd->std_out != 1 && dup2(cmd->std_out, STDOUT_FILENO) == -1)
		perror("dup2");
	close_redir(shell, cmd);
	close_fdlst(shell->lstfd);
	execve(argv[0], argv, env);
	perror("execve");
	gc_free_all(shell->gc);
	exit(errno);
}

static void	which_builtin(t_cmd *cmd)
{
	if (!cmd->argv[0])
	{
		cmd->is_builtin = -1;
		return ;
	}
	if (!ft_strcmp(cmd->argv[0], "echo"))
		cmd->is_builtin = 0;
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		cmd->is_builtin = 2;
	else if (!ft_strcmp(cmd->argv[0], "export"))
		cmd->is_builtin = 3;
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		cmd->is_builtin = 4;
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		cmd->is_builtin = 5;
	else if (!ft_strcmp(cmd->argv[0], "env"))
		cmd->is_builtin = 6;
	else
		cmd->is_builtin = -1;
}
