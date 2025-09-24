/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:02:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/24 14:49:35 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// External includes
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

// Local includes
# include "libft.h"

// Macros

// Structs
typedef struct s_minishell
{
	// add more?
	unsigned int flags;
	struct	s_gc *gc;
}	t_minishell;

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}

typedef struct s_ast
{
	enum e_type 	type;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_token	*token;
}	t_ast;

	

//Prototypes


#endif
