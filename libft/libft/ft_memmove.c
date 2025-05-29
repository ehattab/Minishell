/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:50:27 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:14 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
	{
		d += n;
		s += n;
		while (n--)
		{
			*--d = *--s;
		}
	}
	else
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	return (dst);
}
