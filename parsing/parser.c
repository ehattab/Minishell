/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:01:46 by ehattab           #+#    #+#             */
/*   Updated: 2025/06/03 01:43:43 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*parser(t_token *input_tokens)
{
	t_token		*tokens;
	t_token		*tmp;
	t_commands	*cmds;
	int			nb_word;
	int i = 0;

	nb_word = 0;
	cmds = NULL;
	tokens = input_tokens;
	while (tokens)
	{
		t_commands	*new;
		new = malloc(sizeof(t_commands));
		new->args = NULL;
		new->file_name = NULL;
		new->num_redirections = NULL;
		new->redirections = NULL;
		new->next = NULL;
		new->prev = NULL;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
			{
				tmp = tokens;
				while (tmp && tmp->type != REDIR_IN
				&& tmp->type != REDIR_OUT && tmp->type != REDIR_APPEND
				&& tmp->type != HEREDOC && tmp->type != PIPE)
				{
					if (tmp->type == WORD)
						nb_word++;
					tmp = tmp->next;
				}
				new->args = malloc(sizeof(char *) * (nb_word + 1));
				i = 0;
				while (i <= nb_word)
				{
					new->args[i] = NULL;
					i++;
				}
				add_word(&new, tokens->value);
			}
			else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
			{
				add_redirection(&new, tokens);
				if (tokens->next->type == WORD)
					tokens = tokens->next;
			}
			tokens = tokens->next;
		}
		nb_word = 0;
		add_command(&cmds, new);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}

void	add_word(t_commands **cmd, char *str)
{
	int	i;

	i = 0;
	while ((*cmd)->args[i])
		i++;
	(*cmd)->args[i] = ft_strdup(str);
	(*cmd)->args[i + 1] = NULL;
}

void	add_redirection(t_commands **cmd, t_token *token)
{
	(*cmd)->redirections->type = token->type;
	(*cmd)->redirections->file = token->next->value;
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
