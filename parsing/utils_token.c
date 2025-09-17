/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:23:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/17 15:43:54 by toroman          ###   ########.fr       */
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

void	debug_tokens(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	printf("=== DEBUG TOKENS ===\n");
	while (tmp)
	{
		printf("Token[%d]: '%s' | Type: %d ", i++, tmp->value, tmp->type);
		if (tmp->type == WORD)
			printf("(WORD)\n");
		else if (tmp->type == SIMPLE_QUOTES)
			printf("(SIMPLE_QUOTES)\n");
		else if (tmp->type == DBL_QUOTES)
			printf("(DBL_QUOTES)\n");
		else if (tmp->type == PIPE)
			printf("(PIPE)\n");
		else
			printf("(OTHER)\n");
		tmp = tmp->next;
	}
	printf("==================\n");
}
