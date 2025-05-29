/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:14:28 by ehattab           #+#    #+#             */
/*   Updated: 2024/12/05 15:35:04 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long long	adresse;
	int					i;

	adresse = (unsigned long long) ptr;
	i = 0;
	if (!ptr)
	{
		i += ft_putstr("(nil)");
		return (i);
	}
	i += ft_putstr("0x");
	i += ft_printhexa(adresse, 0);
	return (i);
}
