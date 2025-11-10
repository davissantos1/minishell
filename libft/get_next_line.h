/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:04:53 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/20 21:00:52 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// External includes
# include <stdlib.h>
# include <unistd.h>

// Macro default definition
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Function prototypes
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_indexof(const char *s, int c);
void	*ft_free(void *ptr);

#endif
