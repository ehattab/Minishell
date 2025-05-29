/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:54:30 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:36 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
