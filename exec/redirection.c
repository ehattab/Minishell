/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tony <tony@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:13:41 by toroman           #+#    #+#             */
/*   Updated: 2025/07/28 18:04:42 by tony             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"
#include "../libft/Header/get_next_line.h"

void	parsing_redir(t_commands *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			handle_redir_in(tmp->file);
		else if (tmp->type == REDIR_OUT)
			handle_redir_out(tmp->file);
		else if (tmp->type == REDIR_APPEND)
			append_redir(tmp->file);
		else if (tmp->type == HEREDOC)
			handle_heredoc(tmp->file);
		tmp = tmp->next;
	}
}

void	handle_redir_in(char *value)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_redir_out(char *value)
{
	int	fd;

	fd = open(value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

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
		perror("open");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_heredoc(char *delimeter)
{
	int	fd[2];
	char	*line;

	if(pipe(fd) == -1)
	{
		perror("pipe");
		return;
	}
	while(1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);

		if(!line)
			break;
		if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0 
			&&	line[ft_strlen(delimeter)] == '\n'
			&& 	line[ft_strlen(delimeter) + 1] == '\0')
		{
			free(line);
			break;;
		}
		write(fd[0], line, ft_strlen(delimeter));
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("dup2 heredoc");
	close(fd[0]);
}
