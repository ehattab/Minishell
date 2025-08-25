/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tony <tony@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:41:48 by toroman           #+#    #+#             */
/*   Updated: 2025/08/25 13:32:16 by tony             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	process_input(char *str, t_context *ctx)
{
	t_token		*tokens;
	t_commands	*cmds;
	int			error_status;

	tokens = lexer(str);
	error_status = handle_error(tokens);
	tokens = expander(tokens, ctx);
	if (error_status == 0)
	{
		cmds = parser(tokens);
		if (cmds)
			exec_cmd(cmds, ctx->env, ctx);
		ctx->last_status = 0;
	}
	else
		ctx->last_status = error_status;
	free_all(str, tokens, cmds);
}

void	minishell_loop(t_context *ctx)
{
	char	*str;

	while (1)
	{
		init_signals();
		str = readline("Minishell :");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		if (*str)
			add_history(str);
		process_input(str, ctx);
	}
}

void	reset_signal_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
