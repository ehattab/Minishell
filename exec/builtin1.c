/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:47:02 by toroman           #+#    #+#             */
/*   Updated: 2025/08/04 16:27:05 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	is_numeric_argument(char *str)
{
	int	i = 0;

	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
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

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
		exit(0);
	if (!is_numeric_argument(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit((unsigned char)exit_code);
}

int	builtin_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
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
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
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

int	is_valid_varname(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_var_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, arg, i + 1);
	return (name);
}

int	find_var_env(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	set_var_env(char *arg, char **envp)
{
	char *name;
	int	pos;
	int	j;

	name = get_var_name(arg);
	if (!name)
		return ;
	pos = find_var_env(name, envp);
	free (name);
	if (pos != -1)
	{
		free(envp[pos]);
		envp[pos] = ft_strdup(arg);
	}
	else
	{
		j = 0;
		while (envp[j])
			j++;
		envp[j] = ft_strdup(arg);
		envp[j + 1] = NULL;
	}
}

int	builtin_export(char **args, char **envp)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_varname(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
		}
		else
			set_var_env(args[i], envp);
		i++;
	}
	return (0);
}
