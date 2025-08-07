/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:27:43 by toroman           #+#    #+#             */
/*   Updated: 2025/08/07 16:40:49 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token_value(char *val, t_context *ctx)
{
	char	*result;

	result = ft_strdup("");
	result = expend_value_while(val, result, ctx);
	free(val);
	return (result);
}

char	*expend_value_while(char *val, char *result, t_context *ctx)
{
	int		i;
	int		new_i;
	char	*tmp;

	i = 0;
	while (val[i])
	{
		if (val[i] == '\'' && val[i + 1])
			tmp = handle_single_quote(val, i, &new_i);
		else if (val[i] == '$')
			tmp = handle_dollar_case(val, i, ctx, &new_i);
		else
			tmp = handle_char(val, i, &new_i);
		result = strjoin_and_free(result, tmp);
		i = new_i;
	}
	return (result);
}

char	*handle_dollar_case(char *val, int i, t_context *ctx, int *new_i)
{
	if (!val[i + 1] || (!ft_isalnum(val[i + 1])
			&& val[i + 1] != '_' && val[i + 1] != '?'))
	{
		*new_i = i + 1;
		return (ft_strdup("$"));
	}
	else
		return (handle_dollar(val, i + 1, ctx, new_i));
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

t_token	*expander(t_token *tokens, t_context *ctx)
{
	t_token	*tmp;

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
