/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:28:55 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/02 19:51:47 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		s = "(null)";
	}
	while (*s)
	{
		write(1, s, 1);
		s++;
		count++;
	}
	return (count);
}
