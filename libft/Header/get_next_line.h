/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:06:29 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/23 14:59:34 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stddef.h>
# include <fcntl.h>
# include <string.h>

	// main

char	*get_next_line(int fd);
char	*ft_read(int fd, char *s);
char	*ft_line(char *s);
char	*after(char *s, char *line);

	// utils

int		ft_strlen(const char *str);
char	*ft_strchrs(const char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strdupp(const char *s);

#endif
