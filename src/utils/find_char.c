/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:31:06 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/28 23:58:59 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_break(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (is_meta(str[index]))
			return (&str[index]);
		if (is_space(str[index]))
			return (&str[index]);
		index++;
	}
	return (NULL);
}
