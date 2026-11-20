/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relyaman <relyaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 20:36:05 by relyaman          #+#    #+#             */
/*   Updated: 2026/11/20 20:58:28 by relyaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_next(int fd, char *st)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
	{
		free(st);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(st, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(st);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		st = ft_strjoin(st, buf);
	}
	free(buf);
	return (st);
}

static char	*extract_line(char *st)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!st || !st[0])
		return (NULL);
	while (st[i] && st[i] != '\n')
		i++;
	if (st[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i > 0)
	{
		i--;
		line[i] = st[i];
	}
	return (line);
}

static char	*clean_next(char *st)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (st[i] && st[i] != '\n')
		i++;
	if (!st[i] || !st[i + 1])
	{
		free(st);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(st) - i));
	if (!line)
	{
		free(st);
		return (NULL);
	}
	i++;
	j = 0;
	while (st[i])
		line[j++] = st[i++];
	line[j] = '\0';
	free(st);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*st[FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || FD <= fd)
		return (NULL);
	st[fd] = read_and_next(fd, st[fd]);
	if (!st[fd])
		return (NULL);
	line = extract_line(st[fd]);
	st[fd] = clean_next(st[fd]);
	return (line);
}
