/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toroman <toroman@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:06:32 by toroman           #+#    #+#             */
/*   Updated: 2025/09/09 11:45:02 by toroman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	has_redirection(t_commands *cmd)
{
	return (cmd->redirections != NULL);
}

void	append_redir(char *value)
{
	int	fd;

	fd = open(value, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

void	handle_heredoc(char *delimeter)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	handle_while(fd[1], delimeter);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("dup2 heredoc");
	close(fd[0]);
}

void	handle_while(int fd, char *delimeter)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0
			&& line[ft_strlen(delimeter)] == '\n'
			&& line[ft_strlen(delimeter) + 1] == '\0')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	ignore_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
