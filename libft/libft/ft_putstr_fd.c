/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:28:55 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:28 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

// int main()
// {
//     // Exemple de chaîne à afficher
//     char *str = "Bonjour, voici un test de ft_putstr_fd!\n";
//     // Affiche la chaîne sur la sortie standard (fd 1)
//     ft_putstr_fd(str, 1);
//     // Optionnellement, vous pouvez aussi écrire dans un fichie
//     return 0;
// }
