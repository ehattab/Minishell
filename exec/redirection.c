/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:13:41 by toroman           #+#    #+#             */
/*   Updated: 2025/08/07 16:07:02 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	parsing_redir(t_commands *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			handle_redir_in(tmp->file);
		else if (tmp->type == REDIR_OUT)
			handle_redir_out(tmp->file);
		else if (tmp->type == REDIR_APPEND)
			append_redir(tmp->file);
		else if (tmp->type == HEREDOC)
			handle_heredoc(tmp->file);
		tmp = tmp->next;
	}
}

void	handle_redir_in(char *value)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_redir_out(char *value)
{
	int	fd;

	fd = open(value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}
