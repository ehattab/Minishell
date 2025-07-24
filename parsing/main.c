/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/24 20:26:36 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char		*str;
	t_token		*tokens;
	t_commands	*cmds;
	t_lexer		*l;

	if (ac != 1)
	{
		ft_putendl_fd("This program does not take any arguments", 2);
		exit(1);
	}
	(void)av;
	l = malloc(sizeof(t_lexer));
	if (!l)
	{
		ft_putendl_fd("fatal error: malloc failed", 2);
		return (1);
	}
	ft_bzero(l, sizeof(t_lexer));

	while (1)
	{
		str = readline("Minishell :");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		tokens = lexer(str);
		l->error_status = handle_error(tokens);
		if (l->error_status == 0)
		{
			tokens = expander(tokens, l->error_status);
			cmds = parser(tokens);
			if (cmds)
				print_cmds(&cmds);
		}
		free_all(str, tokens, cmds);
	}
	free(l);
	return (0);
}
