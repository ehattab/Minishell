/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:07:17 by toroman           #+#    #+#             */
/*   Updated: 2025/09/09 19:17:25 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redirection(t_token *token)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = token->type;
	new->file = ft_strdup(token->next->value);
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	add_redirection_to_cmd(t_commands **cmd, t_redir *new)
{
	t_redir	*tmp;

	if (!(*cmd)->redirections)
	{
		(*cmd)->redirections = new;
		return ;
	}
	tmp = (*cmd)->redirections;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

int	copy_array_content(char **array, char **new_array, int count)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			while (--i >= 0)
				free(new_array[i]);
			return (0);
		}
		i++;
	}
	new_array[count] = NULL;
	new_array[count + 1] = NULL;
	return (1);
}

int	process_word_addition(char **new_array, char *str, int size,
							char **original_array)
{
	if (!original_array)
	{
		new_array[0] = ft_strdup(str);
		if (!new_array[0])
			return (0);
		new_array[1] = NULL;
		return (1);
	}
	new_array[size] = ft_strdup(str);
	if (!new_array[size])
		return (0);
	new_array[size + 1] = NULL;
	return (1);
}
