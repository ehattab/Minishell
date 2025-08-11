/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:21 by toroman           #+#    #+#             */
/*   Updated: 2025/08/11 17:07:18 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	exec_all_cmd(t_commands *cmd, char **envp)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
		{
			reset_signal_exec();
			parsing_redir(cmd);
			exec_child(cmd, prev_fd, pipe_fd, envp);
		}
		else if (pid < 0)
			return (perror("fork"));
		handle_parent(&prev_fd, pipe_fd, cmd);
		cmd = cmd->next;
	}
	wait_for_all();
}

void	wait_for_all(void)
{
	int	status;
	int	sig;

	while (wait(&status) > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
			else if (sig == SIGINT)
				write(2, "\n", 1);
		}
	}
}

void	handle_parent(int *prev_fd, int *pipe_fd, t_commands *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	exec_child(t_commands *cmd, int prev_fd, int *pipe_fd, char **envp)
{
	if (ft_strchr(cmd->args[0], '/'))
		execve(cmd->args[0], cmd->args, envp);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (builtin_exec(cmd, envp))
		exit (0);
	cmd->path = find_cmd(cmd->args[0], envp, cmd);
	if (!cmd->path)
	{
		perror("command not found");
		exit(1);
	}
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
