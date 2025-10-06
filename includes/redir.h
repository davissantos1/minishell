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

typedef struct	s_err
{
	char			*file;
	char			*error_msg;
	struct s_err	*next;
}	t_err;

void	find_redir(t_minishell *shell, t_ast *node);
void	do_redir(t_minishell *shell, t_cmd *cmd);

#endif