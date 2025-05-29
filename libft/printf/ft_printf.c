/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:31:27 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/02 19:51:14 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/ft_printf.h"

int	ft_convertion(va_list args, const char s)
{
	unsigned int	i;

	i = 0;
	if (s == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (s == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (s == 'p')
		i += ft_putptr(va_arg(args, void *));
	else if (s == 'd' || s == 'i')
		i += ft_putnbr(va_arg(args, int));
	else if (s == 'u')
		i += ft_uputnbr(va_arg(args, unsigned int));
	else if (s == 'x' || s == 'X')
		i += ft_printhexa(va_arg(args, unsigned int), s == 'X');
	else if (s == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *s, ...)
{
	unsigned int	i;
	unsigned int	y;
	va_list			args;

	va_start(args, s);
	i = 0;
	y = 0;
	while (s[y] != '\0')
	{
		if (s[y] == '%' && s[y + 1])
		{
			i += ft_convertion(args, s[++y]);
		}
		else
			i += ft_putchar(s[y]);
		y++;
	}
	va_end(args);
	return (i);
}

// int main(void)
// {
// 	int	i,j;

// 	i = printf("result :%x.\n", 255);
// 	j = ft_printf("result :%x.\n", 255);
// 	printf("vrai :%d\nft :%d", i, j);
// 	return 0;
// }

// int main() {
//     int x = 42;          // Déclaration d'une variable
//     int *ptr = &x;       // Pointeur pointant vers la variable x

//     // Affichage de l'adresse du pointeur avec %p
//     printf("L'adresse de x est : %p\n", (void*)ptr);

//     // Affichage du contenu de l'adresse pointée par ptr (valeur de x)
//     printf("La valeur de x est : %d\n", *ptr);

// 	// Affichage de l'adresse du pointeur avec %p
//     ft_printf("L'adresse de x est : %p\n", (void*)ptr);

//     // Affichage du contenu de l'adresse pointée par ptr (valeur de x)
//     ft_printf("La valeur de x est : %d\n", *ptr);

//     return 0;
// }
