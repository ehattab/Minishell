/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:30 by ehattab           #+#    #+#             */
/*   Updated: 2025/05/24 15:39:48 by ehattab          ###   ########.fr       */
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
