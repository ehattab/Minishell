/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:08:58 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:43:54 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/get_next_line.h"

char	*ft_read(int fd, char *s)
{
	ssize_t	lu;
	char	*buff;

	if (!s)
		s = ft_strdup("");
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	lu = 1;
	while (!ft_strchr(s, '\n') && lu != 0)
	{
		lu = read(fd, buff, BUFFER_SIZE);
		if (lu <= 0)
		{
			if (s[0] == 0)
				return (free(s), free(buff), NULL);
			else
				return (free(buff), s);
		}
		buff[lu] = '\0';
		s = ft_strjoin(s, buff);
	}
	free(buff);
	return (s);
}

char	*ft_line(char *s)
{
	int		i;
	char	*line;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line [i] = '\0';
	return (line);
}

char	*after(char *s, char *line)
{
	int		i;
	int		j;
	char	*newstash;

	i = 0;
	j = 0;
	while (line[i] && s[i])
	{
		i++;
	}
	newstash = malloc(sizeof(char) * ft_strlen(s) - i + 1);
	if (!newstash)
		return (NULL);
	while (s[i])
	{
		newstash[j] = s[i];
		i++;
		j++;
	}
	newstash[j] = '\0';
	free(s);
	return (newstash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_line(stash);
	stash = after(stash, line);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("txt.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("%s", line);
// 		free(line);
// 	}
// }
