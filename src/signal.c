/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:53:21 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/19 16:52:01 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = (volatile sig_atomic_t) sig;
	}
}

void	signal_child(int sig)
{
	g_signal = (volatile sig_atomic_t) sig;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

void register_parent_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	struct sigaction sa_child;

	rl_catch_signals = 0;
	sa_int.sa_handler = &signal_interrupt;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("Minishell");
	sa_child.sa_handler = &signal_child;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa_child, NULL) == -1)
		perror("Minishell");
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
}

void	register_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
