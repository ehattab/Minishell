/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:21 by toroman           #+#    #+#             */
/*   Updated: 2025/08/08 19:56:24 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	exec_all_cmd(t_commands *cmd, char **envp, t_context *ctx)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
		{
			parsing_redir(cmd);
			exec_child(cmd, prev_fd, pipe_fd, envp, ctx);
		}
		else if (pid < 0)
			return (perror("fork"));
		last_pid = pid;
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
	{
		if (last_pid != -1 && last_pid == waitpid(-1, &status, WNOHANG) && WIFEXITED(status))
			ctx->last_status = WEXITSTATUS(status);
	}
}

void	exec_child(t_commands *cmd, int prev_fd, int *pipe_fd, char **envp, t_context *ctx)
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
	if (builtin_exec(cmd, envp, ctx))
		exit(ctx->last_status);
	path = find_cmd(cmd->args[0], envp, cmd);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		perror("execve");
		exit(126);
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
