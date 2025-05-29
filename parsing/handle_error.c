/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:26:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/05/28 19:09:59 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_lexer *l, t_token *tokens)
{
	t_token	*tmp;
	check_start(l, tokens);
	while (tmp != NULL)
	{
		
	}
}

void	chek_start(t_lexer *l, t_token *t)
{
	if (t->type == REDIR_APPEND || t->type == HEREDOC
	|| t->type == REDIR_IN || t->type == REDIR_OUT || t->type == PIPE)
	{
		
	}
}