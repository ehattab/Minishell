/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:22:39 by toroman           #+#    #+#             */
/*   Updated: 2025/09/18 15:22:57 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	handle_export_arg(char *arg, char **envp, t_context *ctx)
{
	if (!is_valid_varname(arg))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
	}
	else if (ft_strchr(arg, '='))
		set_var_env(arg, envp, ctx);
	return (0);
}
