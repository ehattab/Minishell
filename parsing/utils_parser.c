/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:22:00 by ehattab           #+#    #+#             */
/*   Updated: 2025/08/07 17:01:36 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_commands **head)
{
	t_commands	*tmp;
	t_redir		*r;
	int			i;

	tmp = *head;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			printf("word %d = %s\n", i, tmp->args[i]);
			i++;
		}
		r = tmp->redirections;
		while (r)
		{
			printf("redirections : file = %s, type = %d\n", r->file, r->type);
			r = r->next;
		}
		printf("num redir = %d\n", tmp->num_redirections);
		printf("-------------------------------------\n");
		tmp = tmp->next;
	}
}

void	free_cmds(t_commands **head)
{
	t_commands	*tmp;
	t_commands	*next;

	tmp = *head;
	while (tmp != NULL)
	{
		next = tmp->next;
		free_tab(tmp->args);
		free_redirection(&tmp->redirections);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	free_redirection(t_redir **head)
{
	t_redir	*tmp;
	t_redir	*next;

	tmp = (*head);
	while (tmp)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
