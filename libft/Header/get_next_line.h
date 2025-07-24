/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:06:29 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/24 16:31:52 by ehattab          ###   ########.fr       */
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
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strdup_gnl(const char *s);

#endif
