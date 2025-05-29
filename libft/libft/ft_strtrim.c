/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:32:13 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:59 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rendu;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (s1[i])
	{
		while (s1[j] && ft_strchr(set, s1[j]))
			j--;
	}
	rendu = ft_substr(s1, i, j - i + 1);
	return (rendu);
}
// int main()
// {
//     const char *str1 = "wwwwxxHello, World!xxwwwxwx";
//     const char *set1 = "xw";
//     char *trimmed1 = ft_strtrim(str1, set1);
//     printf("Test 1: '%s' -> '%s'\n", str1, trimmed1);
//     free(trimmed1);
// }
