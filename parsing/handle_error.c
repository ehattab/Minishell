/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:26:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/05/30 18:59:06 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;
	tmp = tokens;
	int i;

	i = 0;
	// check_start(l, tokens);
	while (tmp != NULL)
	{
		i = check_redir(tmp);
		if (i)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

// void	check_start(t_lexer *l, t_token *t)
// {
// 	if (t->type == REDIR_APPEND || t->type == HEREDOC
// 	|| t->type == REDIR_IN || t->type == REDIR_OUT || t->type == PIPE)
// 	{
// 	}
// }

int	check_redir(t_token *t)
{
	if (t->type && t->type == REDIR_APPEND && t->next->type
	&& t->next->type == REDIR_APPEND)
	{
		ft_putendl_fd("syntax error near unexpected token `>>'", 2);
		return (1);
	}
	else if (t->type && t->type == REDIR_APPEND
	&& t->next->type && t->next->type == REDIR_OUT)
	{
		ft_putendl_fd("syntax error near unexpected token `>'", 2);
		return (1);
	}
	else if (t->type && t->type == HEREDOC
	&& t->next->type && t->next->type == HEREDOC)
	{
		ft_putendl_fd("syntax error near unexpected token `<<'", 2);
		return (1);
	}
	else if (t->type && t->type == HEREDOC
	&& t->next->type && t->next->type == REDIR_IN)
	{
		ft_putendl_fd("syntax error near unexpected token `<'", 2);
		return (1);
	}
	return (0);
}
