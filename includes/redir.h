/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:53:02 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/08 16:22:51 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# define PATH_MAX 4096

# include "structs.h"

void	find_heredoc(t_minishell *shell, t_ast *node);
int		heredoc(char *limiter);
void	redirection(t_minishell *shell, t_cmd *cmd);
void	close_redir(t_minishell *shell, t_cmd *cmd);

#endif
