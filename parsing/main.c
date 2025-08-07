/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/07 15:35:35 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int ac, char **av, char **envp)
//{
//    int         error_status;
//    char        *str;
//    t_token     *tokens;
//    t_commands  *cmds;
//    t_context   ctx;

//    if (ac != 1)
//    {
//        ft_putendl_fd("This program does not take any arguments", 2);
//        exit(1);
//    }
//    (void)av;

//    ctx.last_status = 0;
//    ctx.env = copy_env(envp);
//    while (1)
//    {
//        str = readline("Minishell :");
//        if (!str)
//        {
//            printf("exit\n");
//            break ;
//        }
//        add_history(str);
//        cmds = NULL;
//        tokens = lexer(str);
//        error_status = handle_error(tokens);
//        tokens = expander(tokens, &ctx);
//        if (error_status == 0)
//        {
//            cmds = parser(tokens);
//            if (cmds != NULL)
//                exec_cmd(cmds, ctx.env);
//            ctx.last_status = 0;
//        }
//        else
//            ctx.last_status = error_status;
//        free_all(str, tokens, cmds);
//    }
//    return (0);
//}


int	main(int ac, char **av, char **envp)
{
	t_context	ctx;

	if (ac != 1)
	{
		ft_putendl_fd("This program does not take any arguments", 2);
		exit(1);
	}
	(void)av;
	ctx.last_status = 0;
	ctx.env = copy_env(envp);
	minishell_loop(&ctx);
	return (0);
}
