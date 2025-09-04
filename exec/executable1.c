/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:21 by toroman           #+#    #+#             */
/*   Updated: 2025/09/04 15:07:01 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	exec_all_cmd(t_commands *cmd, char **envp, t_context *ctx)
{
	t_fds	fds;
	pid_t	pid;
	pid_t	last_pid;

	fds.prev_fd = -1;
	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fds.pipe_fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
			handle_child_process(cmd, fds, envp, ctx);
		else if (pid < 0)
			return (perror("fork"));
		last_pid = pid;
		update_file_descriptors(&fds.prev_fd, fds.pipe_fd, cmd);
		cmd = cmd->next;
	}
	wait_for_processes(last_pid, ctx);
}

void	exec_child(t_commands *cmd, int *fds, char **envp, t_context *ctx)
{
	char	*path;

	if (ft_strchr(cmd->args[0], '/'))
		execve(cmd->args[0], cmd->args, envp);
	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (cmd->next)
	{
		close(fds[2]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	if (builtin_exec(cmd, envp, ctx))
		exit(ctx->last_status);
	path = find_cmd(cmd->args[0], envp, cmd);
	execute_command_path(cmd, envp, path);
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

void	exec_child_single(t_commands *cmd, char **envp, t_context *ctx)
{
	char	*path;

	parsing_redir(cmd);
	if (builtin_exec(cmd, envp, ctx))
		exit(ctx->last_status);
	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup(cmd->args[0]);
	else
		path = find_cmd(cmd->args[0], envp, cmd);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execute_command(path, cmd->args, envp, cmd->args[0]);
	free(path);
	exit(126);
}

void	execute_command(char *path, char **args, char **envp, char *cmd_name)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": Is a directory", 2);
		free(path);
		exit(126);
	}
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free(path);
		exit(127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		free(path);
		exit(126);
	}
	execve(path, args, envp);
	perror("execve");
}
