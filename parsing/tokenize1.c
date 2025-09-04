/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:08:16 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/04 15:27:59 by toroman          ###   ########.fr       */
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
	return (c == '|' || c == ' ' || c == '\t' || c == '<' || c == '>');
}

char	*build_word_content(t_lexer *l, t_quote_info *info)
{
	char	*word;
	char	*temp;
	int		part_count;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	*info = (t_quote_info){0, 0};
	part_count = 0;
	while (l->str[l->i] && !is_word_delimiter(l->str[l->i]))
	{
		temp = process_segment(l, info, &part_count);
		word = handle_segment_result(l, word, temp);
		if (!word)
			return (NULL);
	}
	if (part_count > 1)
		info->has_multiple_parts = 1;
	return (word);
}
