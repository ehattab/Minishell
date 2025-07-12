/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:26:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/08 20:57:25 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_error(t_token *tokens)
// {
// 	t_token	*tmp;
// 	tmp = tokens;
// 	int i;

// 	i = 0;
// 	while (tmp != NULL)
// 	{
// 		i = check_syntax(tmp);
// 		if (i)
// 			return (i);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	check_syntax(t_token *tokens)
// {
// 	t_token	*tmp;
// 	tmp = tokens;

// 	while (tmp != NULL)
// 	{
// 		if (simple_return(tmp))
// 			return (-1);
// 		else if (check_redir(tmp) || check_pipe(tmp))
// 			return (2);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	check_pipe(t_token *t)
// {
// 	if (t->type && t->type == PIPE
// 		&& (t->next == NULL || t->prev == NULL))
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `|'", 2);
// 		return (1);
// 	}
// 	if (t->type && t->type == PIPE
// 		&& (t->next->type == PIPE || t->prev->type == PIPE))
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `||'", 2);
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_redir(t_token *t)
// {
// 	if (check_redir_args(t))
// 		return (1);
// 	else if (check_redir_dbl(t))
// 		return (1);
// 	return (0);
// }

// int	check_redir_args(t_token *t)
// {
// 	if (t->type && t->type >= REDIR_IN
// 		&& t->type <= HEREDOC && t->next == NULL)
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
// 		return (1);
// 	}
// 	 if (t->type && t->type >= REDIR_IN
// 		&& t->type <= HEREDOC && (t->next->type == PIPE))
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `|'", 2);
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_redir_dbl(t_token *t)
// {
// 	if (t->type && t->type >= REDIR_IN
// 		&& t->type <= HEREDOC && t->next->type == REDIR_APPEND)
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `>>'", 2);
// 		return (1);
// 	}
// 	else if (t->type && t->type >= REDIR_IN
// 		&& t->type <= HEREDOC && t->next->type && t->next->type == REDIR_OUT)
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `>'", 2);
// 		return (1);
// 	}
// 	else if (t->type && t->type >= REDIR_IN
// 		&& t->type <= HEREDOC && t->next->type && t->next->type == HEREDOC)
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `<<'", 2);
// 		return (1);
// 	}
// 	else if (t->type && t->type >= REDIR_IN
// 		&& t->type <= HEREDOC && t->next->type && t->next->type == REDIR_IN)
// 	{
// 		ft_putendl_fd("syntax error near unexpected token `<'", 2);
// 		return (1);
// 	}
// 	return (0);
// }

// int	simple_return(t_token *t)
// {
// 	if (t->value && t->value[0] == ':'
// 	&& (t->next == NULL || t->prev== NULL))
// 		return (1);
// 	else if (t->value && t->value[0] == '!'
// 	&& (t->next == NULL || t->prev == NULL))
// 		return (1);
// 	return (0);
// }
