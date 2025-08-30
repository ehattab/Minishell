/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:08:16 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/30 15:30:04 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quote_segment(t_lexer *l, int quote_type)
{
	char	*temp;
	int		end;

	end = end_quotes(l, quote_type);
	if (end == -1)
	{
		l->error_flag = 1;
		return (NULL);
	}
	temp = ft_substr(l->str, l->i + 1, end - l->i - 1);
	l->i = end + 1;
	return (temp);
}

char	*handle_char_segment(t_lexer *l)
{
	char	*temp;

	temp = malloc(2);
	if (!temp)
		return (NULL);
	temp[0] = l->str[l->i];
	temp[1] = '\0';
	l->i++;
	return (temp);
}

int	is_word_delimiter(char c)
{
	return (c == '|' || c == ' ' || c == '\t'
		|| c == '<' || c == '>');
}

char *build_word_content(t_lexer *l, t_quote_info *info)
{
    char *word;
    char *temp;
    int part_count;
    
    word = ft_strdup("");
    info->has_simple_quotes = 0;
    info->has_multiple_parts = 0;
    part_count = 0;
    if (!word)
        return (NULL);
    while (l->str[l->i] && !is_word_delimiter(l->str[l->i]))
    {
        if (l->str[l->i] == '\'')
        {
            temp = handle_quote_segment(l, SIMPLE_QUOTES);
            info->has_simple_quotes = 1;
            part_count++;
        }
        else if (l->str[l->i] == '\"')
        {
            temp = handle_quote_segment(l, DBL_QUOTES);
            part_count++;
        }
        else
        {
            temp = handle_char_segment(l);
            part_count++;
        }
        if (!temp)
        {
            free(word);
            return (NULL);
        }
        word = strjoin_and_free(word, temp);
        if (!word)
            return (NULL);
    }
    if (part_count > 1)
        info->has_multiple_parts = 1;
    return (word);
}
