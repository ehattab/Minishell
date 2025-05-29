/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/05/28 16:29:07 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*str;
	t_token	*tokens;

	if (ac != 1)
	{
		ft_putendl_fd("This program does not take any arguments\n", 2);
		exit(1);
	}
	(void) ac;
	(void) av;
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
		free(str);
		if (tokens != NULL)
		{
			print_token(&tokens);
			free_token(&tokens);
		}
	}
}