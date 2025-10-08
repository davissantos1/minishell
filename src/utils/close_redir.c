/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:40:00 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/08 19:40:01 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redir(t_cmd *cmd)
{
	if (cmd->std_in != -1 && cmd->std_in != 0)
		close(cmd->std_in);
	if (cmd->std_out != -1 && cmd->std_in != 1)
		close(cmd->std_out);
}
