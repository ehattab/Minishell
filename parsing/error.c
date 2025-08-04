/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:56:49 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/31 18:41:42 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(char *token)
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

int	check_pipe_syntax(t_token *t)
{
	if (!t || t->type != PIPE)
		return (0);
	if (!t->prev || !t->next)
		return (print_syntax_error("|"));
	if (t->prev->type == PIPE || t->next->type == PIPE)
		return (print_syntax_error("|"));
	return (0);
}

int	check_redirection_token(t_token *t)
{
	if (!t)
		return (0);
	if (t->type < REDIR_IN || t->type > HEREDOC)
		return (0);
	if (!t->next)
		return (print_syntax_error(NULL));
	if (t->next->type == PIPE)
		return (print_syntax_error("|"));
	if (t->next->type >= REDIR_IN && t->next->type <= HEREDOC)
	{
		if (t->next->value)
			return (print_syntax_error(t->next->value));
		else
			return (print_syntax_error(NULL));
	}
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

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (check_disallowed_token(tmp))
			return (100);
		if (check_pipe_syntax(tmp))
			return (2);
		if (check_redirection_token(tmp))
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
