/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:30:23 by toroman           #+#    #+#             */
/*   Updated: 2025/07/19 15:48:05 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	count_cmd(t_commands *cmd)
{
	int	count;

	count = 0;
	while(cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	exec_cmd(t_commands *cmd, char **envp)
{
	pid_t	pid;
	char	*commande;
	char	*path;
	int		status;

	if (count_cmd(cmd) == 1)
	{
		commande = cmd->args[0];
		path = find_cmd(commande, envp, cmd);
		if (!path)
		{
			perror("command not found : ");
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			parsing_redir(cmd);
			if(execve(path, cmd->args, envp) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else if (pid > 0)
			waitpid(pid, &status, 0);
		else
			perror("fork");
	}
}

char	*get_path(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char *args, char **env, t_commands *cmd)
{
	char	**path_split;
	char	*path_join;
	char	*tpm;
	int		i;

	cmd->path = get_path("PATH=", env);
	path_split = ft_split(cmd->path, ':');
	if (!path_split)
		return (NULL);
	i = 0;
	while (path_split[i])
	{
		tpm = ft_strjoin(path_split[i], "/");
		path_join = ft_strjoin(tpm, args);
		if (access(path_join, X_OK) == 0)
			return (path_join);
		free(path_join);
		i++;
	}
	ft_free(path_split);
	return (NULL);
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


void	exec_all_cmd(t_commands *cmd, char **envp)
{
	int	pipe_fd[2];
	int	prev_fd;
	pid_t pid;
	int	status;
	char	*path;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				return;
			}
		}
		pid = fork();
		if (pid == 0)
		{
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
			parsing_redir(cmd);
			path = find_cmd(cmd->args[0], envp, cmd);
			if(!path)
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
		else if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0);
}
