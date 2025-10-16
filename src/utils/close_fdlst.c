/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fdlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:50:23 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 11:51:34 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fdlst(t_lstint *node_fd)
{
	while (node_fd)
	{
		close(node_fd->value);
		node_fd = node_fd->next;
	}
}
