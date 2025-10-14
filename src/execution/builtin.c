/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:47:50 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 17:24:31 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_minishell *shell, t_cmd *cmd)
{
	printf("aqui em builtin, %i %i", shell->std_in, cmd->std_in);
}
