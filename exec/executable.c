/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:30:23 by toroman           #+#    #+#             */
/*   Updated: 2025/08/08 19:03:34 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	count_cmd(t_commands *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	exec_cmd(t_commands *cmd, char **envp, t_context *ctx)
{
	pid_t	pid;
	int		status;

	if (count_cmd(cmd) != 1)
		return (exec_all_cmd(cmd, envp, ctx));
	if (!has_redirection(cmd) && is_builtin(cmd))
	{
		builtin_exec(cmd, envp, ctx);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		parsing_redir(cmd);
		if (builtin_exec(cmd, envp, ctx))
			exit(ctx->last_status);
		exec_all_cmd(cmd, envp, ctx);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ctx->last_status = WEXITSTATUS(status);
		else
			ctx->last_status = 1;
	}
	else
		perror("fork");
}


void	exec_single_cmd(t_commands *cmd, char **envp)
{
	char	*path;

	path = find_cmd(cmd->args[0], envp, cmd);
	if (!path)
	{
		perror("command not found : ");
		return ;
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		perror("execve");
		exit(1);
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
