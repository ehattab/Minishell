/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:23:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/03 21:01:17 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, enum e_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(str);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_token(t_token **head, char *str, enum e_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = create_token(str, type);
	if (!new)
	{
		ft_putendl_fd("minishell: memory allocation failed in add_token", 2);
		return ;
	}
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
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
