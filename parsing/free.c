/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:25:35 by ehattab           #+#    #+#             */
/*   Updated: 2025/06/16 15:19:40 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char *str, t_token *t, t_commands *commands)
{
	if (str)
		free(str);
	if (t)
		free_token(&t);
	if (commands)
		free_cmds(&commands);
}
