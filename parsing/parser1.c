/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:19:47 by toroman           #+#    #+#             */
/*   Updated: 2025/09/09 18:44:19 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*init_new_command(void)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->num_redirections = 0;
	new->redirections = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->path = NULL;
	return (new);
}

int	process_command_tokens(t_token **tokens, t_commands *new_cmd)
{
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == REDIR_IN || (*tokens)->type == REDIR_OUT
			|| (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
		{
			if (!(*tokens)->next || (*tokens)->next->type != WORD)
				return (0);
			add_redirection(&new_cmd, *tokens);
			*tokens = (*tokens)->next->next;
		}
		else if ((*tokens)->type == WORD)
		{
			new_cmd->args = add_word(new_cmd->args, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else
			*tokens = (*tokens)->next;
	}
	return (1);
}

char	*process_segment(t_lexer *l, t_quote_info *info, int *part_count)
{
	char	*temp;

	temp = NULL;
	if (l->str[l->i] == '\'')
	{
		temp = handle_quote_segment(l, SIMPLE_QUOTES);
		info->has_simple_quotes = 1;
		(*part_count)++;
	}
	else if (l->str[l->i] == '\"')
	{
		temp = handle_quote_segment(l, DBL_QUOTES);
		(*part_count)++;
	}
	else
	{
		temp = handle_char_segment(l);
		(*part_count)++;
	}
	return (temp);
}

char	*handle_segment_result(t_lexer *l, char *word, char *temp)
{
	char	*result;

	if (!temp && l->error_flag)
	{
		free(word);
		return (NULL);
	}
	if (!temp)
		temp = ft_strdup("");
	if (!temp)
	{
		free(word);
		return (NULL);
	}
	result = strjoin_and_free(word, temp);
	if (!result)
	{
		l->error_flag = 1;
		return (NULL);
	}
	return (result);
}
