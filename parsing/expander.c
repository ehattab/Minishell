/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:42:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/30 14:59:34 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_context *ctx)
{
	int		i;
	int		len;
	char	*itoa;

	if (ft_strcmp(name, "?") == 0)
	{
		itoa = ft_itoa(ctx->last_status);
		if (!itoa)
			return (ft_strdup(""));
		return (itoa);
	}
	len = ft_strlen(name);
	i = 0;
	while (ctx->env[i])
	{
		if (!ft_strncmp(ctx->env[i], name, len) && ctx->env[i][len] == '=')
			return (ft_strdup(ctx->env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*extract_var_name(char *str, int index, int *new_index)
{
	int		start;
	int		len;
	char	*name;

	start = index;
	len = 0;
	if (str[index] == '?')
	{
		if (new_index)
			*new_index = index + 1;
		return (ft_strdup("?"));
	}
	while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
	{
		index++;
		len++;
	}
	if (new_index)
		*new_index = index;
	name = ft_substr(str, start, len);
	return (name);
}

char	*handle_dollar(char *val, int i, t_context *ctx, int *new_i)
{
	char	*var;
	char	*value;

	var = extract_var_name(val, i, new_i);
	value = ft_getenv(var, ctx);
	free(var);
	return (value);
}

char	*handle_char(char *val, int i, int *new_i)
{
	char	tmp[2];

	tmp[0] = val[i];
	tmp[1] = '\0';
	*new_i = i + 1;
	return (ft_strdup(tmp));
}

// char	*handle_single_quote(char *val, int i, int *new_i)
// {
// 	char	tmp[2];

// 	tmp[0] = val[i + 1];
// 	tmp[1] = '\0';
// 	*new_i = i + 2;
// 	return (ft_strdup(tmp));
// }
