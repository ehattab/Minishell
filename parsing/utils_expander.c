/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:40:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/19 18:42:50 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_dollar(const char *str)
{
	int	i;
	int	*tab;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			j++;
		i++;
	}
	tab = malloc(sizeof(int) * (j + 1));
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tab[j] = i;
			j++;
		}
		i++;
	}
	return (tab);
}
