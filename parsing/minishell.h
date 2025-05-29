/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:34:30 by ehattab           #+#    #+#             */
/*   Updated: 2025/05/24 19:59:12 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/Header/libft.h"
# include "../libft/Header/ft_printf.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

enum	token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	SIMPLE_QUOTES,
	DBL_QUOTES
};

typedef struct	s_token
{
	char				*value;
	enum token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef	struct	s_lexer
{
	int		error_flag;
	char	*str;
	int		i;
}	t_lexer;

void	free_all(t_lexer *l, t_token *t);
void	add_token(t_token **head,char *str, enum token_type class);
void	print_token(t_token **head);
void	free_token(t_token **head);
t_token	*lexer(char *str);
void	initialise_lexer(char *str, t_lexer **l, t_token **tokens);
t_token	*last_token(t_token **head);
void	tokenize_next(t_token **t, t_lexer *l);
int		end_quotes(t_lexer *l, int e);
void	tokenize_quotes(t_token **t, t_lexer *l, int e);
void	tokenize_pipe(t_token **t, t_lexer *l, int e);
void	tokenize_word(t_token **t, t_lexer *l, int e);
void	tokenize_append_heredoc(t_token **t, t_lexer *l, int type);
void	tokenize_redir(t_token **t, t_lexer *l, int type);

#endif