/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:01:46 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/04 15:21:14 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*parser(t_token *input_tokens)
{
	t_token		*tokens;
	t_commands	*cmds;
	t_commands	*new;

	cmds = NULL;
	tokens = input_tokens;
	while (tokens)
	{
		new = init_new_command();
		if (!new)
			return (free_cmds(&cmds), NULL);
		if (!process_command_tokens(&tokens, new))
		{
			free_cmds(&cmds);
			free(new);
			return (NULL);
		}
		add_command(&cmds, new);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}

void	add_redirection(t_commands **cmd, t_token *token)
{
	t_redir	*tmp;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	new->type = token->type;
	new->file = ft_strdup(token->next->value);
	new->next = NULL;
	(*cmd)->num_redirections++;
	if (!(*cmd)->redirections)
	{
		(*cmd)->redirections = new;
		return ;
	}
	else
	{
		tmp = (*cmd)->redirections;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_command(t_commands **head, t_commands *new)
{
	t_commands	*tmp;

	if (!*head)
	{
		(*head) = new;
		(*head)->prev = NULL;
		return ;
	}
	tmp = (*head);
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
}

char	**add_word(char **array, char *str)
{
	char	**new_array;
	int		size;

	new_array = copy_existing_array(array, &size);
	if (!new_array)
		return (NULL);
	if (!array)
	{
		new_array[0] = ft_strdup(str);
		new_array[1] = NULL;
		return (new_array);
	}
	new_array[size] = ft_strdup(str);
	new_array[size + 1] = NULL;
	free_tab(array);
	return (new_array);
}

char	**copy_existing_array(char **array, int *size)
{
	char	**new_array;
	int		i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	*size = i;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	return (new_array);
}
