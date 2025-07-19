/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:42:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/19 19:34:57 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cast_expander(char *name)
{
	char	*value;

	value = ft_strdup(getenv(name));
	return (value);
}

void	manage_expander(int error_status, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == WORD)
			
	}
}

int	check_expand(char *str, int *tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[j])
	{
		if (str[tab[j + 1]] == '?')
			
	}
}