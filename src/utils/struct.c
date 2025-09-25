#include "minishell.h"

t_minishell	*shell_init(char **env)
{
	t_gc 		*garbage;
	t_minishell	*shell;

	garbage = gc_init();
	if (!garbage)
		exit_code(NULL, EXIT_FAILURE);
	shell = gc_malloc(sizeof(t_minishell), garbage, GC_DEFAULT);
	if (!shell)
		exit_code(NULL, EXIT_FAILURE);
	shell->gc = garbage;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->root = NULL;
	shell->env = env;
	shell->fd0 = dup(STDIN_FILENO);
	shell->fd1 = dup(STDOUT_FILENO);
	shell->fd2 = dup(STDERR_FILENO);
	if (shell->fd0 == -1 || shell->fd1 == -1 || shell->fd2 == -1) 
		exit_code(shell, EXIT_FAILURE);
	shell->exit = 0;
	return (shell);
}
