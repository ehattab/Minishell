/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/06/30 18:22:03 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char		*str;
	t_token		*tokens;
	t_commands	*cmds;
	int			error_num;

	error_num = 0;
	if (ac != 1)
	{
		ft_putendl_fd("This program does not take any arguments", 2);
		exit(1);
	}
	(void) ac;
	(void) av;
	cmds = NULL;
	while (1)
	{
		str = readline("Minishell :");
		if (!str)
		{
			printf("exit\n");
			break;
		}
		add_history(str);
		tokens = lexer(str);
		// error_num = check_syntax(tokens);
		if (!error_num)
		{
			cmds = parser(tokens);
			if (cmds != NULL)
				print_cmds(&cmds);
			builtin_exec(cmds);
		}
		else
			error_num = 0;
		free_all(str, tokens, cmds);
	}
}
