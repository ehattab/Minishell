/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:52:01 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:11 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;
	size_t				i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}
