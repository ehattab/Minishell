/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:40:53 by ehattab           #+#    #+#             */
/*   Updated: 2025/09/09 18:44:19 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **tokens, t_token *to_remove)
{
	if (!tokens || !*tokens || !to_remove)
		return ;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (*tokens == to_remove)
		*tokens = to_remove->next;
	free(to_remove->value);
	free(to_remove);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == WORD && (!tmp->value || tmp->value[0] == '\0'))
		{
			if (!(tmp->value && ft_strcmp(tmp->value, "$") == 0))
				remove_token(tokens, tmp);
		}
		tmp = next;
	}
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
