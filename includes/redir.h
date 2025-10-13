/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:53:02 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 16:56:37 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# define PATH_MAX 4096

# include "minishell.h"

typedef struct s_redir
{
	t_node_type		type;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

void	find_heredoc(t_minishell *shell, t_ast *node);
int		heredoc(char *limiter);
void	redirection(t_minishell *shell, t_cmd *cmd);
void	close_redir(t_cmd *cmd);

#endif