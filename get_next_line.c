/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relyaman <relyaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 11:15:01 by relyaman          #+#    #+#             */
/*   Updated: 2026/11/17 17:00:32 by relyaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//serch to now line '\n'
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*next;
	char	*buff;
	char	*tmp;
	int			n;

	n = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (n != 0)
	{	
		if (ft_strchr(tmp, '\n'))
		{
			
		}
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return (NULL);
		n = read(fd, buff, BUFFER_SIZE);
		if (n <= 0)
			return (NULL);
		tmp = 
		free(buff);
		buff = NULL;
		
	}
}
