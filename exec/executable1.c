/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:21 by toroman           #+#    #+#             */
/*   Updated: 2025/08/18 19:37:48 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    exec_all_cmd(t_commands *cmd, char **envp, t_context *ctx)
{
    int     pipe_fd[2];
    int     prev_fd = -1;
    pid_t   pid, last_pid = -1;
    int     status;

    while (cmd) {
        if (cmd->next && pipe(pipe_fd) == -1)
            return (perror("pipe"));
        pid = fork();
        if (pid == 0) {
            parsing_redir(cmd);
            exec_child(cmd, prev_fd, pipe_fd, envp, ctx);
        } else if (pid < 0) {
            return (perror("fork"));
        }
        last_pid = pid;
        if (prev_fd != -1) close(prev_fd);
        if (cmd->next) {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
        cmd = cmd->next;
    }

    // D'abord le dernier (code du pipe selon bash)
    if (last_pid != -1) {
        waitpid(last_pid, &status, 0);
        if (WIFEXITED(status))
            ctx->last_status = WEXITSTATUS(status);
        else
            ctx->last_status = 1;
    }
    // Puis on “récolte” les autres
    while (wait(NULL) > 0) {;}
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
	char *path = NULL;

	parsing_redir(cmd);

	if (builtin_exec(cmd, envp, ctx))
		exit(ctx->last_status);

    // Si l’argument contient un '/', on l’utilise tel quel (./a.out, /bin/ls, etc.)
	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup(cmd->args[0]);
	else
		path = find_cmd(cmd->args[0], envp, cmd); // recherche dans PATH

	if (!path) {
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127); // introuvable
	}

    // Fichier trouvé mais non exécutable → 126
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0) {
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		free(path);
		exit(126);
    }

    execve(path, cmd->args, envp);

    // En cas d'échec d'execve, affiner le code de sortie
    int e = errno;
    if (e == EACCES) {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putendl_fd(": Permission denied", 2);
        exit(126);
    } else if (e == ENOENT) {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putendl_fd(": No such file or directory", 2);
        exit(127);
    } else if (e == EISDIR) {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putendl_fd(": Is a directory", 2);
        exit(126);
    } else {
        perror("execve");
        exit(126);
    }
}
