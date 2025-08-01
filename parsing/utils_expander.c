/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:40:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/01 18:32:36 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **tokens, t_token *to_remove)
{
	if (!tokens || !*tokens || !to_remove)
		return ;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (*tokens == to_remove)
		*tokens = to_remove->next;
	free(to_remove->value);
	free(to_remove);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == WORD
			&& (!tmp->value || tmp->value[0] == '\0')
			&& !(tmp->value && tmp->value[0] == '$' && tmp->value[1] == '\0'))
		{
			remove_token(tokens, tmp);
		}
		tmp = next;
	}
}
