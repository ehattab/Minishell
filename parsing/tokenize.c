/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:29:04 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/04 18:27:55 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_quotes(t_lexer *l, int type)
{
	int	j;

	j = l->i + 1;
	if (type == SIMPLE_QUOTES)
	{
		while (l->str[j] && l->str[j] != '\'')
			j++;
	}
	else
	{
		while (l->str[j] && l->str[j] != '\"')
			j++;
	}
	if (l->str[j] == '\0')
	{
		ft_putendl_fd("The quote(s) is not closed", 2);
		return (-1);
	}
	else
		return (j);
}

void	tokenize_quotes(t_token **t, t_lexer *l, int type)
{
	int	j;

	j = end_quotes(l, type);
	if (j == -1)
	{
		l->error_flag = 1;
		return ;
	}
	add_token(t, ft_substr(l->str, l->i + 1, j- l->i - 1), WORD);
	l->i = j + 1;
	return ;
}

void	tokenize_pipe(t_token **t, t_lexer *l, int type)
{
	if (l->str[l->i + 1] == '|')
	{
		ft_putendl_fd("syntax error near unexpected token `||'", 2);
		l->error_flag = 1;
		return ;
	}
	l->i++;
	add_token(t, ft_strdup("|"), type);
}

void	tokenize_word(t_token **t, t_lexer *l, int type)
{
	int	start;

	start = l->i;
	while (l->str[l->i] && l->str[l->i] != '|' && l->str[l->i] != '\''
	&& l->str[l->i] != '\"' && l->str[l->i] != '<' 
	&& l->str[l->i] != '>'
	&& l->str[l->i] != ' ' && l->str[l->i] != '\t')
		l->i++;
	add_token(t, ft_substr(l->str, start, l->i - start), type);
}
