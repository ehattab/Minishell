/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/09 12:02:27 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arguments(int ac)
{
	if (ac != 1)
	{
		ft_putendl_fd("This program does not take any arguments", 2);
		return (1);
	}
	return (0);
}

void	process_command(char *str, t_context *ctx)
{
	t_token		*tokens;
	t_commands	*cmds;
	int			error_status;

	tokens = lexer(str);
	error_status = handle_error(tokens);
	if (error_status == 0)
	{
		tokens = expander(tokens, ctx);
		cmds = parser(tokens);
		if (cmds != NULL)
			exec_cmd(cmds, ctx->env, ctx);
	}
	else
		ctx->last_status = error_status;
	free_all(str, tokens, cmds);
}

int	main(int ac, char **av, char **envp)
{
	t_context	ctx;
	char		*str;

	if (check_arguments(ac))
		exit(1);
	(void)av;
	ctx.last_status = 0;
	ctx.env = copy_env(envp);

	init_signals();
	while (1)
	{
		str = readline("Minishell :");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		process_command(str, &ctx);
	}
	rl_clear_history();
	return (0);
}
