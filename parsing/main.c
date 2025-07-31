/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/31 19:39:13 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	int			error_status;
	char		*str;
	t_token		*tokens;
	t_commands	*cmds;
	t_context	ctx;

	if (ac != 1)
	{
		ft_putendl_fd("This program does not take any arguments", 2);
		exit(1);
	}
	(void)av;
	ctx.last_status = 0;
	while (1)
	{
		str = readline("Minishell :");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		cmds = NULL;
		tokens = lexer(str);
		error_status = handle_error(tokens);
		tokens = expander(tokens, &ctx);
		if (ctx.last_status == 0)
		{
			cmds = parser(tokens);
			if (cmds)
				print_cmds(&cmds);
		}
		else
			ctx.last_status = error_status;
		free_all(str, tokens, cmds);
	}
	return (0);
}
