/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:37:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/29 21:31:05 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_context ctx;
    int error_status;
    char *str;
    t_token *tokens;
    t_commands *cmds;
    
    if (ac != 1)
    {
        ft_putendl_fd("This program does not take any arguments", 2);
        exit(1);
    }
    (void)av;
    ctx.last_status = 0;
    ctx.env = copy_env(envp);
    
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
        
        // 1. Lexer d'abord
        tokens = lexer(str);
        
        // 2. Vérifier les erreurs de syntaxe
        error_status = handle_error(tokens);
        
        // 3. Si pas d'erreur, faire l'expansion puis parser
        if (error_status == 0)
        {
            tokens = expander(tokens, &ctx);  // Expansion après vérification
            cmds = parser(tokens);
            if (cmds != NULL)
                exec_cmd(cmds, ctx.env, &ctx);
        }
        else
            ctx.last_status = error_status;
            
        free_all(str, tokens, cmds);
    }
    return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_context	ctx;
//      int         error_status;
//    char        *str;
//    t_token     *tokens;
//    t_commands  *cmds;


// 	if (ac != 1)
//     {
//         ft_putendl_fd("This program does not take any arguments", 2);
// 		exit(1);
// 	}
// 	(void)av;

//     ctx.last_status = 0;
//     ctx.env = copy_env(envp);
//     while (1)
//     {
//         str = readline("Minishell :");
//         if (!str)
//         {
//             printf("exit\n");
//             break ;
//         }
//         add_history(str);
//         cmds = NULL;
//         tokens = lexer(str);
//         error_status = handle_error(tokens);
//         tokens = expander(tokens, &ctx);
//         if (error_status == 0)
//         {
//             cmds = parser(tokens);
//             if (cmds != NULL)
//                 exec_cmd(cmds, ctx.env, &ctx);
//             // ctx.last_status = 0;
//         }
//         else
//             ctx.last_status = error_status;
//         free_all(str, tokens, cmds);
//     }
//     return (0);
// }
