/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:42:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/01 18:45:07 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_context *ctx)
{
	char	*itoa;

	if (ft_strcmp(name, "?") == 0)
	{
		itoa = ft_itoa(ctx->last_status);
		if (!itoa)
			return (ft_strdup(""));
		return (itoa);
	}
	if (!getenv(name))
		return (ft_strdup(""));
	return (ft_strdup(getenv(name)));
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

char	*handle_single_quote(char *val, int i, int *new_i)
{
	char	tmp[2];

	tmp[0] = val[i + 1];
	tmp[1] = '\0';
	*new_i = i + 2;
	return (ft_strdup(tmp));
}

char	*expand_token_value(char *val, t_context *ctx)
{
	char	*result;
	char	*tmp;
	int		i;
	int		new_i;

	i = 0;
	result = ft_strdup("");
	while (val[i])
	{
		if (val[i] == '\'' && val[i + 1])
			tmp = handle_single_quote(val, i, &new_i);
		else if (val[i] == '$')
		{
			if (!val[i + 1] || (!ft_isalnum(val[i + 1]) && val[i + 1] != '_' && val[i + 1] != '?'))
			{
				tmp = ft_strdup("$");
				new_i = i + 1;
			}
			else
				tmp = handle_dollar(val, i + 1, ctx, &new_i);
		}
		else
			tmp = handle_char(val, i, &new_i);
		result = strjoin_and_free(result, tmp);
		i = new_i;
	}
	free(val);
	return (result);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char *res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

t_token	*expander(t_token *tokens, t_context *ctx)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->value, '$'))
			tmp->value = expand_token_value(tmp->value, ctx);
		tmp = tmp->next;
	}
	remove_empty_tokens(&tokens);
	return (tokens);
}
