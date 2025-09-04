/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:37:06 by toroman           #+#    #+#             */
/*   Updated: 2025/09/04 15:07:49 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char	*search_command_in_paths(char *cmd, char **path_split)
{
	char	*path_join;
	char	*tmp;
	int		i;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		if (!tmp)
			return (NULL);
		path_join = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path_join)
			return (NULL);
		if (access(path_join, X_OK) == 0)
		{
			ft_free(path_split);
			return (path_join);
		}
		free(path_join);
		i++;
	}
	ft_free(path_split);
	return (NULL);
}

void	execute_command_path(t_commands *cmd, char **envp, char *path)
{
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		free(path);
		exit(126);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		perror("execve");
		free(path);
		exit(126);
	}
}

void	handle_child_process(t_commands *cmd, t_fds fds, char **envp,
		t_context *ctx)
{
	parsing_redir(cmd);
	if (fds.prev_fd != -1)
	{
		dup2(fds.prev_fd, STDIN_FILENO);
		close(fds.prev_fd);
	}
	if (cmd->next)
	{
		close(fds.pipe_fd[0]);
		dup2(fds.pipe_fd[1], STDOUT_FILENO);
		close(fds.pipe_fd[1]);
	}
	exec_child_single(cmd, envp, ctx);
}

void	update_file_descriptors(int *prev_fd, int *pipe_fd, t_commands *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

void	wait_for_processes(pid_t last_pid, t_context *ctx)
{
	int	status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			ctx->last_status = WEXITSTATUS(status);
		else
			ctx->last_status = 1;
	}
	while (wait(NULL) > 0)
		;
}
