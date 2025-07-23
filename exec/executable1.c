/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:21 by toroman           #+#    #+#             */
/*   Updated: 2025/07/23 16:01:22 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	exec_all_cmd(t_commands *cmd, char **envp)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
		{
			parsing_redir(cmd);
			exec_child(cmd, prev_fd, pipe_fd, envp);
		}
		else if (pid < 0)
			return (perror("fork"));
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
}

void	exec_child(t_commands *cmd, int prev_fd, int *pipe_fd, char **envp)
{
	char	*path;

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
	if (builtin_exec(cmd))
		exit (0);
	path = find_cmd(cmd->args[0], envp, cmd);
	if (!path)
	{
		perror("command not found");
		exit(1);
	}
	if (execve(path, cmd->args, envp) == -1)
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
