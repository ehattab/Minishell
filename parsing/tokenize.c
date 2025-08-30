/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:29:04 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/30 18:08:47 by ehattab          ###   ########.fr       */
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

void tokenize_quotes(t_token **t, t_lexer *l, int type)
{
    int j;
    j = end_quotes(l, type);
    if (j == -1)
    {
        l->error_flag = 1;
        return ;
    }
    add_token(t, ft_substr(l->str, l->i + 1, j - l->i - 1), type);
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
	char			*word;
	t_quote_info	info;

	if (l->error_flag)
		return ;
	word = build_word_content(l, &info);
	if (!word)
	{
		if (!l->error_flag)
			l->error_flag = 1;
		return ;
	}
	if (word[0] || (word[0] == '\0' && info.has_simple_quotes))
	{
		if (info.has_multiple_parts)
			add_token(t, word, WORD);
		else if (info.has_simple_quotes)
			add_token(t, word, SIMPLE_QUOTES);
		else
			add_token(t, word, type);
	}
	else
		free(word);
}
