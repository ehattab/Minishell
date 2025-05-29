/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:53:22 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:16 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr++ = c;
	}
	return (s);
}
