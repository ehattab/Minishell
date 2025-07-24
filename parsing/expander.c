/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:42:11 by ehattab           #+#    #+#             */
/*   Updated: 2025/07/24 21:00:09 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char	*env;

	env = getenv(name);
	if (!env)
		return (ft_strdup(""));
	return (ft_strdup(env));
}

char	*expand_var(const char *str, int *status, int *len)
{
	char	*name;
	char	*value;

	if (str[0] == '?' && (!str[1] || str[1] == ' ' || str[1] == '\t'))
	{
		*len = 1;
		return (ft_itoa(*status));
	}
	*len = 0;
	while (str[*len] && (ft_isalnum(str[*len]) || str[*len] == '_'))
		(*len)++;
	name = ft_substr(str, 0, *len);
	value = ft_getenv(name);
	free(name);
	return (value);
}

char	*handle_single_quote(const char *line, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

char	*expand_line(const char *line, int *status)
{
	char	*result;
	char	*part;
	int		i;
	int		len;

	i = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '\'')
		{
			part = handle_single_quote(line, &i);
			result = ft_strjoin_free(result, part, 3);
		}
		else if (line[i] == '$')
		{
			part = expand_var(&line[i + 1], status, &len);
			i += len + 1;
			result = ft_strjoin_free(result, part, 3);
		}
		else
		{
			char tmp[2];
			tmp[0] = line[i];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, ft_strdup(tmp), 3);
			i++;
		}
	}
	return (result);
}

t_token	*expander(t_token *tokens, int last_status)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->value && ft_strchr(tmp->value, '$'))
		{
			expanded = expand_line(tmp->value, &last_status);
			if (expanded)
			{
				free(tmp->value);
				tmp->value = expanded;
			}
		}
		tmp = tmp->next;
	}
	return (tokens);
}

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = ft_strjoin(s1, s2);
	if ((to_free == 1 || to_free == 3) && s1)
		free(s1);
	if ((to_free == 2 || to_free == 3) && s2)
		free(s2);
	return (res);
}
