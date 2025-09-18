/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:25:35 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/03 21:01:28 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char *str, t_token *t, t_commands *commands)
{
	if (str)
		free(str);
	if (t)
		free_token(&t);
	if (commands)
		free_cmds(&commands);
}

void	free_token(t_token **head)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *head;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
