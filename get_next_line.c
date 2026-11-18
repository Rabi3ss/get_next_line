/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relyaman <relyaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 11:15:01 by relyaman          #+#    #+#             */
/*   Updated: 2026/11/18 15:57:29 by relyaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_next(int fd, char *next)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
	{
		free(next);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(next, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(next);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		next = ft_strjoin(next, buf);
	}
	free(buf);
	return (next);
}

static char	*extract_line(char *next)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!next || !next[0])
		return (NULL);
	while (next[i] && next[i] != '\n')
		i++;
	if (next[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i > 0)
	{
		i--;
		line[i] = next[i];
	}
	return (line);
}

static char	*clean_next(char *next)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (next[i] && next[i] != '\n')
		i++;
	if (!next[i] || !next[i + 1])
	{
		free(next);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(next) - i));
	if (!line)
	{
		free(next);
		return (NULL);
	}
	i++;
	j = 0;
	while (next[i])
		line[j++] = next[i++];
	line[j] = '\0';
	free(next);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*st;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	st = read_and_next(fd, st);
	if (!st)
		return (NULL);
	line = extract_line(st);
	st = clean_next(st);
	return (line);
}