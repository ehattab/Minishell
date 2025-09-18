/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:56:49 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/30 18:11:04 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (2);
}

char	*check_pipe_syntax(t_token *t)
{
	if (!t || t->type != PIPE)
		return (NULL);
	// Si le pipe est en début ou fin de ligne, ou double pipe
	if (!t->prev || !t->next)
		return ("|");
	if ((t->prev && t->prev->type == PIPE) || (t->next && t->next->type == PIPE))
		return ("|");
	return (NULL);
}

char	*check_redirection_token(t_token *t)
{
	if (!t)
		return (NULL);
	if (t->type < REDIR_IN || t->type > HEREDOC)
		return (NULL);
	// Si la redirection est seule ou suivie d'un token non valide
	if (!t->next)
		return (t->value);
	if (t->next->type == PIPE)
		return (t->value);
	if (t->next->type >= REDIR_IN && t->next->type <= HEREDOC)
		return (t->value);
	// Si la redirection est suivie d'un mot vide ou NULL
	if (t->next->type == WORD && (!t->next->value || t->next->value[0] == '\0'))
		return (t->value);
	return (NULL);
}

int	check_double_operators(t_token *t)
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

int	check_heredoc_syntax(t_token *t)
{
	if (!t || t->type != HEREDOC)
		return (0);
	if (!t->next || t->next->type != WORD)
		return (print_syntax_error(NULL));
	return (0);
}
