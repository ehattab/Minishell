/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:55:33 by toroman           #+#    #+#             */
/*   Updated: 2025/09/18 15:25:27 by toroman          ###   ########.fr       */
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

void	set_var_env(char *arg, char **envp, t_context *ctx)
{
	char	*name;
	int		pos;

	name = get_var_name(arg);
	if (!name)
		return ;
	pos = find_var_env(name, envp);
	free(name);
	if (pos != -1)
		update_existing_var(envp, pos, arg);
	else
		add_new_var(ctx, arg);
}

int	builtin_export(char **args, char **envp, t_context *ctx)
{
	int	i;
	int	status;
	int	local_status;

	status = 0;
	if (!args[1])
	{
		print_exported_vars(envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		local_status = handle_export_arg(args[i], envp, ctx);
		if (local_status == 1)
			status = 1;
		i++;
	}
	return (status);
}
