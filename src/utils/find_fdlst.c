/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fdlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 08:05:53 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/31 08:07:11 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*find_fd(t_lstint *lst, int fd)
{
	if (!lst)
		return (NULL);
	while (lst && lst->value != fd)
		lst = lst->next;
	return (lst);
}
