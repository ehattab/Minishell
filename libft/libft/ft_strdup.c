/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:52:46 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:34 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*src;
	char	*dest;

	i = 0;
	len = 0;
	src = (char *)s;
	while (src[len])
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// int	main()
// {
// 	char	*str;
// 	char	*new_str;
// 	str = "wesh bien";
// 	new_str = ft_strdup(str);
// 	printf("%s\n", new_str);
// 	free (new_str);
// }
