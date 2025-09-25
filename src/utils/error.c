#include "minishell.h"

void	exit_code(t_minishell *shell, int code)
{
	if (shell)
		gc_free_all(shell->gc);
	if (code != 0)
		perror("minishell");
	exit(code);
}
