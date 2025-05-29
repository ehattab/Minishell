/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:23:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/05/24 19:24:22 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **head,char *str, enum token_type class)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		{
			ft_printf("Error\n");
			return ;
		}
	new->value = str;
	new->type = class;
	new->next = NULL;
	new->prev = NULL;
	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
}

void	print_token(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("value = %s, type = %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}

void	free_token(t_token **head)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *head;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

t_token	*last_token(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
