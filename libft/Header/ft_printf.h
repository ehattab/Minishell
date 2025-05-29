/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:56:41 by ehattab           #+#    #+#             */
/*   Updated: 2024/12/12 19:31:16 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int				ft_printf(const char *s, ...);
int				ft_putchar(int c);
int				ft_putstr(char *s);
int				ft_putnbr(int n);
unsigned int	ft_uputnbr(unsigned int n);
int				ft_printhexa(unsigned long long n, int s);
int				ft_putptr(void *ptr);

#endif