/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:42:12 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/02 19:51:50 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/ft_printf.h"

unsigned int	ft_uputnbr(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_uputnbr(n / 10);
	}
	i += ft_putchar((n % 10) + '0');
	return (i);
}
