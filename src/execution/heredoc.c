/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:24:53 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/07 14:23:09 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tmp_file(char path[PATH_MAX]);
static void	warning(char *limiter);

int	heredoc(t_minishell *shell, char *limiter)
{
	char	*str;
	char	path[PATH_MAX];
	int		fd;

	tmp_file(path);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		str = readline("> ");
		if (g_signal || str == NULL || !ft_strcmp(str, limiter))
			break ;
		ft_putendl_fd(expand_line(shell, str), fd);
		free(str);
	}
	if (str)
		free(str);
	else
		warning(limiter);
	close(fd);
	if (g_signal)
		fd = -1;
	else
		fd = open(path, O_RDONLY);
	unlink(path);
	return (fd);
}

static void	tmp_file(char path[PATH_MAX])
{
	char	*str;
	int		num;

	ft_bzero(path, PATH_MAX);
	ft_memcpy(path, "/tmp/minishell_heredoc-", 23);
	num = 0;
	while (access(path, F_OK) != -1)
	{
		str = ft_itoa(num);
		ft_strlcat(path, str, PATH_MAX);
		num++;
		free(str);
	}
}

static void	warning(char *limiter)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file", 2);
	ft_putstr_fd(" (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}
