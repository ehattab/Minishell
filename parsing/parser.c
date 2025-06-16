/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:01:46 by ehattab           #+#    #+#             */
/*   Updated: 2025/06/16 18:09:43 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*parser(t_token *input_tokens)
{
	t_token		*tokens;
	t_commands	*cmds;

	cmds = NULL;
	tokens = input_tokens;
	while (tokens)
	{
		t_commands	*new;
		new = malloc(sizeof(t_commands));
		new->args = NULL;
		new->num_redirections = 0;
		new->redirections = NULL;
		new->next = NULL;
		new->prev = NULL;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
			{
				add_redirection(&new, tokens);
				tokens = tokens->next;
			}
			else if (tokens->type == WORD)
			{
				new->args = add_word(new->args, tokens->value);
			}
			tokens = tokens->next;
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
	int		i;
	char	**new_array;
	
	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	if (!array)
	{
		new_array[0] = ft_strdup(str);
		new_array[1] = NULL;
		return (new_array);
	}
	else
	{
		while (array[i])
		{
			new_array[i] = ft_strdup(array[i]);
			i++;
		}
		free_tab(array);
	}
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	return (new_array);
}
