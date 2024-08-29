/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:05:44 by gicomlan          #+#    #+#             */
/*   Updated: 2024/08/29 12:07:46 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strmanip(char *s1, char *s2, int mode)
{
	char	*result;
	int		len_s1;
	int		len_s2;

	result = s1;
	len_s1 = 0;
	len_s2 = 0;
	while (s1 && s1[len_s1] && (mode == 1 || mode == 2))
		len_s1++;
	while (s2 && s2[len_s2] && mode != 1)
		len_s2++;
	if (mode == 1)
		return (ft_strchr(s1, len_s2));
	if (mode == 2)
		return (ft_strjoin(s1, s2, len_s1, len_s2));
	return (ft_strcpy(result, s2));
}

static char	*ft_strchr(char *str, int ch)
{
	while (*str)
	{
		if (*str == (char)ch)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

static char	*ft_strjoin(char *s1, char *s2, int len_s1, int len_s2)
{
	char	*result;
	int		index;

	if (!s1 || !s2)
		return (free(s1), NULL);
	result = malloc(len_s1 + len_s2 + 1);
	if (!result)
		return (free(s1), NULL);
	index = 0;
	while (index < len_s1)
	{
		result[index] = s1[index];
		index++;
	}
	while (index < len_s1 + len_s2)
	{
		result[index] = s2[index - len_s1];
		index++;
	}
	result[index] = '\0';
	return (free(s1), result);
}

static char	*ft_read_line(int fd, char *line, char *buffer)
{
	int		bytes_read;
	char	*newline;

	newline = NULL;
	while (!newline && line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_strmanip(line, buffer, 2);
		newline = ft_strmanip(line, "\n", 1);
	}
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strmanip(buffer, NULL, 3);
	line = ft_read_line(fd, line, buffer);
	if (!line)
		return (NULL);
	newline = ft_strmanip(line, "\n", 1);
	if (newline)
	{
		ft_strmanip(buffer, newline + 1, 3);
		*(newline + 1) = '\0';
	}
	else
		buffer[0] = '\0';
	return (line);
}
