/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:13:47 by toroman           #+#    #+#             */
/*   Updated: 2025/08/07 16:54:30 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_disallowed_token(t_token *t)
{
	if (!t || !t->value || !t->value[0])
		return (0);
	if ((t->value[0] == ':' || t->value[0] == '!') && (!t->next || !t->prev))
		return (1);
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;
	char	*err_token;

	tmp = tokens;
	while (tmp)
	{
		if (check_disallowed_token(tmp))
			return (print_syntax_error(tmp->value));
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
