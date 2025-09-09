/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:01:46 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/09 19:14:02 by toroman          ###   ########.fr       */
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
	t_redir	*new;

	new = create_redirection(token);
	if (!new)
		return ;
	add_redirection_to_cmd(cmd, new);
	(*cmd)->num_redirections++;
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
	if (process_word_addition(new_array, str, size, array))
	{
		free_tab(array);
		return (new_array);
	}
	free_tab(new_array);
	return (array);
}

char	**copy_existing_array(char **array, int *size)
{
	char	**new_array;
	int		count;

	count = 0;
	if (array)
	{
		while (array[count])
			count++;
	}
	*size = count;
	new_array = malloc(sizeof(char *) * (count + 2));
	if (!new_array)
		return (NULL);
	if (!copy_array_content(array, new_array, count))
		return (NULL);
	return (new_array);
}
