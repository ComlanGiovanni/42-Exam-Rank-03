/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:04:36 by gicomlan          #+#    #+#             */
/*   Updated: 2024/08/29 12:04:37 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	char	*tmp;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	tmp = res;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}

static char	*ft_update_line(char *line, char *buffer)
{
	char	*tmp;
	char	*newline;

	tmp = ft_strjoin(line, buffer);
	free(line);
	if (!tmp)
		return (NULL);
	newline = ft_strchr(tmp, '\n');
	if (newline)
	{
		*++newline = '\0';
		ft_strchr(buffer, '\0');
		while (*newline)
			*buffer++ = *newline++;
		*buffer = '\0';
	}
	else
		buffer[0] = '\0';
	return (tmp);
}

static char	*ft_read_line(int fd, char *line, char *buffer)
{
	int		read_bytes;
	char	*tmp;

	while (!ft_strchr(line, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = ft_update_line(line, buffer);
		if (!tmp)
			return (NULL);
		line = tmp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strjoin("", buffer);
	if (!line)
		return (NULL);
	line = ft_read_line(fd, line, buffer);
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
