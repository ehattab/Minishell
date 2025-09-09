/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:13:41 by toroman           #+#    #+#             */
/*   Updated: 2025/09/09 11:57:51 by toroman          ###   ########.fr       */
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
		exit (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit (1);
	}
	close(fd);
}

void	handle_redir_out(char *value)
{
	int	fd;

	fd = open(value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(value);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit (1);
	}
	close(fd);
}

int	wait_for_single(pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(2, "\n", 1);
	}
	return (status);
}

void	parent_wait_and_handle_signal(pid_t pid, t_context *ctx)
{
	int	status;

	ignore_parent_signals();
	status = wait_for_single(pid);
	reset_signal_exec();
	
	if (WIFEXITED(status))
		ctx->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ctx->last_status = 128 + WTERMSIG(status);
}
