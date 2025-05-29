/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:05:44 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/02 19:51:35 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/ft_printf.h"

int	ft_printhexa(unsigned long long n, int s)
{
	char	*base;
	int		i;

	i = 0;
	if (s)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		i += ft_printhexa(n / 16, s);
	i += ft_putchar(base[n % 16]);
	return (i);
}
