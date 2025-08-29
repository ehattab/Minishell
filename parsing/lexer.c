/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:16:19 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/29 20:59:58 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lexer(char *str)
{
    t_token *tokens;
    t_lexer *l;
    initialise_lexer(str, &l, &tokens);
    while (l->str[l->i])
    {
        while (l->str[l->i] == ' ' || l->str[l->i] == '\t')
            l->i++;
        if (!l->str[l->i])
            break ;
        tokenize_next(&tokens, l);
        if (l->error_flag)
            return (NULL);
    }
    free(l->str);
    free(l);
    return (tokens);
}

void tokenize_next(t_token **t, t_lexer *l)
{
    if (l->error_flag)
        return ;
    if (l->str[l->i] == '\'')
        tokenize_quotes(t, l, SIMPLE_QUOTES);
    else if (l->str[l->i] == '|')
        tokenize_pipe(t, l, PIPE);
    else if (l->str[l->i] == '\"')
        tokenize_quotes(t, l, DBL_QUOTES);
    else if (l->str[l->i] == '>' && l->str[l->i + 1] == '>')
        tokenize_append(t, l, REDIR_APPEND);
    else if (l->str[l->i] == '<' && l->str[l->i + 1] == '<')
        tokenize_heredoc(t, l, HEREDOC);
    else if (l->str[l->i] == '>')
        tokenize_redir(t, l, REDIR_OUT);
    else if (l->str[l->i] == '<')
        tokenize_redir(t, l, REDIR_IN);
    else
        tokenize_word(t, l, WORD);
}

void	tokenize_append(t_token **t, t_lexer *l, int type)
{
	add_token(t, ft_strdup(">>"), type);
	l->i += 2;
}

void	tokenize_heredoc(t_token **t, t_lexer *l, int type)
{
	add_token(t, ft_strdup("<<"), type);
	l->i += 2;
}

void	tokenize_redir(t_token **t, t_lexer *l, int type)
{
	if (l->str[l->i] == '>')
		add_token(t, ft_strdup(">"), type);
	else if (l->str[l->i] == '<')
		add_token(t, ft_strdup("<"), type);
	l->i++;
}
