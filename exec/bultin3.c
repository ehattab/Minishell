/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:52:09 by toroman           #+#    #+#             */
/*   Updated: 2025/09/09 19:05:00 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	print_exported_vars(char **envp)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (envp[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return ;
	i = -1;
	while (envp[++i])
		env_copy[i] = envp[i];
	env_copy[i] = NULL;
	sort_env_copy(env_copy);
	i = -1;
	while (env_copy[++i])
		print_var_with_quotes(env_copy[i]);
	free(env_copy);
}

void	sort_env_copy(char **env_copy)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (env_copy[++i])
	{
		j = i;
		while (env_copy[++j])
		{
			if (ft_strcmp(env_copy[i], env_copy[j]) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
		}
	}
}

void	print_var_with_quotes(char *env_var)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		var_name = ft_substr(env_var, 0, equal_sign - env_var);
		var_value = equal_sign + 1;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(var_name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(var_value, 1);
		ft_putstr_fd("\"\n", 1);
		free(var_name);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	update_existing_var(char **envp, int pos, char *arg)
{
	free(envp[pos]);
	envp[pos] = ft_strdup(arg);
	if (!envp[pos])
		envp[pos] = NULL;
}

void	add_new_var(char **envp, char *arg)
{
	int	j;

	j = 0;
	while (envp[j])
		j++;
	envp[j] = ft_strdup(arg);
	if (!envp[j])
		return ;
	envp[j + 1] = NULL;
}
