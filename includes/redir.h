/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:53:02 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/06 15:53:03 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# define PATH_MAX 4096

typedef struct s_redir
{
	t_node_type		type;
	char			*file;
}	t_redir;

void	find_heredoc(t_minishell *shell, t_ast *node);
void	redirection(t_minishell *shell, t_cmd *cmd);
void	close_redir(t_cmd *cmd);

#endif