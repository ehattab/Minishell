/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:37:17 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:42:01 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rendu;
	size_t	slen;
	size_t	j;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	rendu = malloc(sizeof(char) * (len + 1));
	if (rendu == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		rendu[j] = s[start];
		j++;
		start++;
	}
	rendu[j] = '\0';
	return (rendu);
}
// int main(void)
// {
//     char s[] = "ashwaganda";
//     char *sub = ft_substr(s, 4, 3);
//     if(sub != NULL)
//     {
//         printf("%s", sub);
//     }
//     free(sub);
//     return 0;
// }
