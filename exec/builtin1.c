/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:47:02 by toroman           #+#    #+#             */
/*   Updated: 2025/08/28 16:27:14 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	is_numeric_argument(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	int	exit_code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
		exit(0);
	if (!is_numeric_argument(args[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(" numeric argument required", STDERR_FILENO);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd(" too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit((unsigned char)exit_code);
}

int	is_builtin(t_commands *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	return (0);
}

void	remove_from_env(char *var, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
		{
			free (envp[i]);
			j = i;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
			return ;
		}
		i++;
	}
}

int	builtin_unset(char **args, char **envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_from_env(args[i], envp);
		i++;
	}
	return (0);
}
