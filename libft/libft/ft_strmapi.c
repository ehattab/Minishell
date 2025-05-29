/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:59:49 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:49 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rendu;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	rendu = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!rendu)
		return (NULL);
	while (s[i])
	{
		rendu[i] = f(i, s[i]);
		i++;
	}
	rendu[i] = '\0';
	return (rendu);
}
