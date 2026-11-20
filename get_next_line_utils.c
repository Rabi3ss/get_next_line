/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relyaman <relyaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:17:12 by relyaman          #+#    #+#             */
/*   Updated: 2026/11/20 20:58:03 by relyaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static void	strjoin_copy(char *str, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	strjoin_copy(str, s1, s2);
	free(s1);
	return (str);
}
