/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:34:30 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/23 16:16:22 by toroman          ###   ########.fr       */
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
# include <fcntl.h>
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

typedef	struct	s_lexer
{
	int		error_flag;
	char	*str;
	int		i;
}	t_lexer;

typedef struct	s_token
{
	char			*value;
	enum token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct	s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_commands
{
	int					num_redirections;
	char				**args;
	t_redir				*redirections;
	struct s_commands	*next;
	struct s_commands	*prev;
	char				*path;

}	t_commands;

void		free_all(char *str, t_token *t, t_commands *commands);
void		add_token(t_token **head,char *str, enum token_type class);
void		print_token(t_token **head);
void		free_token(t_token **head);
t_token		*lexer(char *str);
void		initialise_lexer(char *str, t_lexer **l, t_token **tokens);
t_token		*last_token(t_token **head);
void		tokenize_next(t_token **t, t_lexer *l);
int			end_quotes(t_lexer *l, int e);
void		tokenize_quotes(t_token **t, t_lexer *l, int type);
void		tokenize_pipe(t_token **t, t_lexer *l, int type);
void		tokenize_word(t_token **t, t_lexer *l, int type);
void		tokenize_append(t_token **t, t_lexer *l, int type);
void		tokenize_heredoc(t_token **t, t_lexer *l, int type);
void		tokenize_redir(t_token **t, t_lexer *l, int type);
int			check_syntax(t_token *tokens);
// void		check_start(t_lexer *l, t_token *t);
int			check_redir(t_token *t);
t_commands	*parser(t_token *input_tokens);
void		add_command(t_commands **head, t_commands *new);
void		add_redirection(t_commands **cmd, t_token *token);
char		**add_word(char **array, char *str);
void		print_cmds(t_commands **head);
void		free_cmds(t_commands **head);
void		free_redirection(t_redir **head);
void		free_tab(char **tab);

int			check_n_option(const char *str);
int			builtin_echo(char **args);
int			builtin_exec(t_commands *cmd);
int			builtin_cd(char **cmd);
int			builtin_pwd(void);
void		parsing_redir(t_commands *cmd);
void		handle_redir_in(char *value);
void		handle_redir_out(char *value);
int			count_cmd(t_commands *cmd);
void		exec_cmd(t_commands *cmd, char **envp);
char		*get_path(char *str, char **envp);
char		*find_cmd(char *cmd, char **envp, t_commands *str);
void		ft_free(char **str);
void		exec_all_cmd(t_commands *cmd, char **envp);
void		exec_single_cmd(t_commands *cmd, char **envp);
void		exec_child(t_commands *cmd, int prev_fd, int *pipe_fd, char **envp);
int			builtin_env(char **envp);
int			builtin_exit(char **args);
int			is_numeric_argument(char *str);
int			has_redirection(t_commands *cmd);
int			is_builtin(t_commands *cmd);

#endif
