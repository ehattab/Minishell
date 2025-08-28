/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:21 by toroman           #+#    #+#             */
/*   Updated: 2025/08/28 16:20:33 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void exec_all_cmd(t_commands *cmd, char **envp, t_context *ctx)
{
    int pipe_fd[2];
    int prev_fd = -1;
    pid_t pid, last_pid = -1;
    int status;

    while (cmd)
    {
        if (cmd->next && pipe(pipe_fd) == -1)
            return perror("pipe");

        pid = fork();
        if (pid == 0) 
		{
            parsing_redir(cmd);
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
            exec_child_single(cmd, envp, ctx);
        }
        else if (pid < 0)
            return perror("fork");

        last_pid = pid;

        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next) {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }

        cmd = cmd->next;
    }
    if (last_pid != -1) {
        waitpid(last_pid, &status, 0);
        if (WIFEXITED(status))
            ctx->last_status = WEXITSTATUS(status);
        else
            ctx->last_status = 1;
    }
    while (wait(NULL) > 0);
}


void	exec_child(t_commands *cmd, int prev_fd, int *pipe_fd, char **envp, t_context *ctx)
{
	char	*path;

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
	if (builtin_exec(cmd, envp, ctx))
		exit(ctx->last_status);
	path = find_cmd(cmd->args[0], envp, cmd);
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
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		perror("execve");
		free(path);
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

void exec_child_single(t_commands *cmd, char **envp, t_context *ctx)
{
    char *path;
	struct stat st;

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
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putendl_fd(": Is a directory", 2);
        free(path);
        exit(126);
    }
    if (access(path, F_OK) != 0) {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putendl_fd(": No such file or directory", 2);
        free(path);
        exit(127);
    }
    if (access(path, X_OK) != 0) {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putendl_fd(": Permission denied", 2);
        free(path);
        exit(126);
    }
    execve(path, cmd->args, envp);
    perror("execve");
    free(path);
    exit(126);
}
