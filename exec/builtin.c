/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:29:14 by toroman           #+#    #+#             */
/*   Updated: 2025/06/30 18:14:57 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"


int	builtin_exec(t_commands *cmd)
{
	if (!cmd || !cmd->args[0] || !cmd->args)
		return (0);
	if (strcmp((cmd)->args[0], "echo") == 0)
		return (builtin_echo(cmd->args), 1);
	return (0);
}


int	check_n_option(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;

	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	check_n;

	i = 1;
	check_n = 0;
	while (args[i] && check_n_option(args[i]))
	{
		check_n = 1;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!check_n)
		printf("\n");
	return (0);
}



//int main(void)
//{
//    char *args[] = {"echo", "-n", "hello", "world", NULL};

//    builtin_echo(args);

//    return (0);
//}

//void	check_cd_home(char **args)
//{
//	char *home;

//	if (args[1] != NULL)
//		return;
//	home = getenv("HOME");
//	if(!home)
//	{
//		ft_putendl_fd("cd : home not set", 2);
//	}
//	if (chdir(home) != 0)
//	{
//		perror("cd");
//		return;
//	}
//}
