/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:55:33 by toroman           #+#    #+#             */
/*   Updated: 2025/09/09 18:44:19 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

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
	char	*name;
	int		pos;
	int		j;

	name = get_var_name(arg);
	if (!name)
		return ;
	pos = find_var_env(name, envp);
	free(name);
	if (pos != -1)
	{
		free(envp[pos]);
		envp[pos] = ft_strdup(arg);
		if (!envp[pos])
			envp[pos] = NULL;
	}
	else
	{
		j = 0;
		while (envp[j])
			j++;
		envp[j] = ft_strdup(arg);
		if (!envp[j])
			return ;
		envp[j + 1] = NULL;
	}
}

int	builtin_export(char **args, char **envp)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		print_exported_vars(envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_varname(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
			status = 1;
		}
		else
			set_var_env(args[i], envp);
		i++;
	}
	return (status);
}
