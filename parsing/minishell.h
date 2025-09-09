/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:34:30 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/09 19:17:07 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/Header/ft_printf.h"
# include "../libft/Header/get_next_line.h"
# include "../libft/Header/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

enum					e_token_type
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

typedef struct s_lexer
{
	int					error_flag;
	char				*str;
	int					i;
}						t_lexer;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*value;
	enum e_token_type	type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_quote_info
{
	int					has_simple_quotes;
	int					has_multiple_parts;
}						t_quote_info;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_commands
{
	int					num_redirections;
	char				**args;
	t_redir				*redirections;
	struct s_commands	*next;
	struct s_commands	*prev;
	char				*path;

}						t_commands;

typedef struct s_context
{
	char				**env;
	int					last_status;
}						t_context;

typedef struct s_fds
{
	int					prev_fd;
	int					pipe_fd[2];
}						t_fds;

void					free_all(char *str, t_token *t, t_commands *commands);
t_token					*create_token(char *str, enum e_token_type type);
void					add_token(t_token **head, char *str,
							enum e_token_type type);
void					print_token(t_token **head);
void					free_token(t_token **head);
t_token					*lexer(char *str);
void					initialise_lexer(char *str, t_lexer **l,
							t_token **tokens);
t_token					*last_token(t_token **head);
void					tokenize_next(t_token **t, t_lexer *l);
int						end_quotes(t_lexer *l, int e);
void					tokenize_quotes(t_token **t, t_lexer *l, int type);
void					tokenize_pipe(t_token **t, t_lexer *l, int type);
void					tokenize_word(t_token **t, t_lexer *l, int type);
void					tokenize_append(t_token **t, t_lexer *l, int type);
void					tokenize_heredoc(t_token **t, t_lexer *l, int type);
void					tokenize_redir(t_token **t, t_lexer *l, int type);
int						handle_error(t_token *tokens);
int						check_syntax(t_token *tokens);
int						check_disallowed_token(t_token *t);
char					*check_redirection_token(t_token *t);
char					*check_pipe_syntax(t_token *t);
int						print_syntax_error(char *token);
t_commands				*parser(t_token *input_tokens);
void					add_command(t_commands **head, t_commands *new);
void					add_redirection(t_commands **cmd, t_token *token);
char					**add_word(char **array, char *str);
void					print_cmds(t_commands **head);
void					free_cmds(t_commands **head);
void					free_redirection(t_redir **head);
void					free_tab(char **tab);
t_token					*expander(t_token *tokens, t_context *ctx);
char					*ft_getenv(char *name, t_context *ctx);
char					**copy_env(char **envp);
char					*handle_dollar(char *val, int i, t_context *ctx,
							int *new_i);
char					*extract_var_name(char *str, int index, int *new_index);
char					*expand_token_value(char *val, t_context *ctx);
char					*strjoin_and_free(char *s1, char *s2);
void					remove_empty_tokens(t_token **tokens);
char					*expend_value_while(char *val, char *result,
							t_context *ctx);
char					*handle_dollar_case(char *val, int i, t_context *ctx,
							int *new_i);
void					debug_tokens(t_token *tokens);
char					*handle_quote_segment(t_lexer *l, int quote_type);
char					*handle_char_segment(t_lexer *l);
int						is_word_delimiter(char c);
char					*build_word_content(t_lexer *l, t_quote_info *info);
int						check_arguments(int ac);
void					process_command(char *str, t_context *ctx);
char					**copy_existing_array(char **array, int *size);
int						process_command_tokens(t_token **tokens,
							t_commands *new_cmd);
t_commands				*init_new_command(void);
char					*process_segment(t_lexer *l, t_quote_info *info,
							int *part_count);
char					*handle_segment_result(t_lexer *l, char *word,
							char *temp);
int						check_double_operators(t_token *t);
int						check_heredoc_syntax(t_token *t);
char					*handle_char(char *val, int i, int *new_i);
t_redir					*create_redirection(t_token *token);
void					add_redirection_to_cmd(t_commands **cmd, t_redir *new);
int						copy_array_content(char **array, char **new_array,
							int count);
int						process_word_addition(char **new_array, char *str,
							int size, char **original_array);

int						check_n_option(const char *str);
int						builtin_echo(char **args);
int						builtin_cd(char **cmd);
int						builtin_pwd(void);
void					parsing_redir(t_commands *cmd);
void					handle_redir_in(char *value);
void					handle_redir_out(char *value);
int						count_cmd(t_commands *cmd);
char					*get_path(char *str, char **envp);
char					*find_cmd(char *cmd, char **envp, t_commands *str);
void					ft_free(char **str);
int						is_numeric_argument(char *str);
int						has_redirection(t_commands *cmd);
int						is_builtin(t_commands *cmd);
void					append_redir(char *value);
void					handle_heredoc(char *delimeter);
void					remove_from_env(char *var, char **envp);
int						builtin_unset(char **args, char **envp);
int						is_valid_varname(char *str);
char					*get_var_name(char *arg);
void					set_var_env(char *arg, char **envp);
int						builtin_export(char **args, char **envp);
void					init_signals(void);
void					handle_sigint(int sig);
void					process_input(char *str, t_context *ctx);
void					minishell_loop(t_context *ctx);
void					handle_while(int fd, char *delimeter);
void					reset_signal_exec(void);
int						wait_for_single(pid_t pid);
void					ignore_parent_signals(void);
void					parent_wait_and_handle_signal(pid_t pid,
							t_context *ctx);
char					*search_command_in_paths(char *cmd, char **path_split);
void					execute_command(char *path, char **args, char **envp,
							char *cmd_name);
void					execute_command_path(t_commands *cmd, char **envp,
							char *path);
void					handle_child_process(t_commands *cmd, t_fds fds,
							char **envp, t_context *ctx);
void					update_file_descriptors(int *prev_fd, int *pipe_fd,
							t_commands *cmd);
void					wait_for_processes(pid_t last_pid, t_context *ctx);
void					print_exported_vars(char **envp);
void					sort_env_copy(char **env_copy);
void					print_var_with_quotes(char *env_var);
int						builtin_exec(t_commands *cmd, char **envp,
							t_context *ctx);
void					exec_cmd(t_commands *cmd, char **envp, t_context *ctx);
void					exec_all_cmd(t_commands *cmd, char **envp,
							t_context *ctx);
void					exec_single_cmd(t_commands *cmd, char **envp);
void					exec_child(t_commands *cmd, int *fds, char **envp,
							t_context *ctx);
int						builtin_exit(char **args);
void					exec_child_single(t_commands *cmd, char **envp,
							t_context *ctx);
void					update_existing_var(char **envp, int pos, char *arg);
void					add_new_var(char **envp, char *arg);

#endif
