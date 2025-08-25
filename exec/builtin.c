/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tony <tony@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:29:14 by toroman           #+#    #+#             */
/*   Updated: 2025/08/25 13:27:48 by tony             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	builtin_exec(t_commands *cmd, char **envp, t_context *ctx)
{
	if (!cmd || !cmd->args[0] || !cmd->args)
		return (0);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (ctx->last_status = builtin_echo(cmd->args), 1);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (ctx->last_status = builtin_cd(cmd->args), 1);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (ctx->last_status = builtin_pwd(), 1);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (ctx->last_status = builtin_exit(cmd->args), 1);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (ctx->last_status = builtin_unset(cmd->args, envp), 1);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (ctx->last_status = builtin_export(cmd->args, envp), 1);
	return (0);
}

int	check_n_option(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
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
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (check_n != 1)
		printf("\n");
	return (0);
}

int	builtin_cd(char **cmd)
{
	char	*path;

	if (!cmd[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		path = cmd[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror ("pwd");
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (0);
}
