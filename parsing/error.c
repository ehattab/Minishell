/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:56:49 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/04 19:15:35 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_syntax_error(char *token)
{
    if (!token)
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
    else
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putstr_fd(token, 2);
        ft_putendl_fd("'", 2);
    }
    return (2);
}


char *check_pipe_syntax(t_token *t)
{
    if (!t || t->type != PIPE)
        return (NULL);
    if (!t->prev || !t->next)
        return ("|");
    if (t->prev->type == PIPE || t->next->type == PIPE)
        return ("|");
    return (NULL);
}

char *check_redirection_token(t_token *t)
{
    if (!t)
        return (NULL);
    if (t->type < REDIR_IN || t->type > HEREDOC)
        return (NULL);
    if (!t->next)
        return (NULL);
    if (t->next->type == PIPE)
        return ("|");
    if (t->next->type >= REDIR_IN && t->next->type <= HEREDOC)
        return (t->next->value ? t->next->value : NULL);
    return (NULL);
}

int check_double_operators(t_token *t)
{
    if (!t || !t->value)
        return (0);
    if (ft_strcmp(t->value, "&&") == 0)
        return (print_syntax_error("&&"));
    if (ft_strcmp(t->value, "||") == 0)
        return (print_syntax_error("||"));
    if (ft_strcmp(t->value, ";;;") == 0)
        return (print_syntax_error(";;;"));
    return (0);
}

int check_heredoc_syntax(t_token *t)
{
    if (!t || t->type != HEREDOC)
        return (0);
    if (!t->next || t->next->type != WORD)
        return (print_syntax_error(NULL));
    return (0);
}

int	check_disallowed_token(t_token *t)
{
	if (!t || !t->value || !t->value[0])
		return (0);
	if ((t->value[0] == ':' || t->value[0] == '!')
		&& (!t->next || !t->prev))
		return (1);
	return (0);
}

int check_syntax(t_token *tokens)
{
    t_token *tmp;
    char    *err_token;

    tmp = tokens;
    while (tmp)
    {
        if (check_disallowed_token(tmp))
            return print_syntax_error(tmp->value);
        if (check_double_operators(tmp))
            return (2);
        err_token = check_pipe_syntax(tmp);
        if (err_token)
            return (print_syntax_error(err_token));
        err_token = check_redirection_token(tmp);
        if (err_token)
            return (print_syntax_error(err_token));
        if (check_heredoc_syntax(tmp))
            return (2);
        tmp = tmp->next;
    }
    return (0);
}


int	handle_error(t_token *tokens)
{
	if (!tokens)
		return (0);
	return (check_syntax(tokens));
}
