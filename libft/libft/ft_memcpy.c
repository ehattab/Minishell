/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:38:33 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:12 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
