/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:30 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/07 16:54:17 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialise_lexer(char *str, t_lexer **l, t_token **tokens)
{
	*l = malloc(sizeof(t_lexer));
	(*l)->str = ft_strdup(str);
	(*l)->i = 0;
	(*l)->error_flag = 0;
	*tokens = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
