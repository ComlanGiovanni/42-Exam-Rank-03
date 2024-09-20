/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_refator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:03:10 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/17 23:00:58 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *string, int character)
{
	while (*string)
	{
		if (*string == (char)character)
			return ((char *)string);
		string++;
	}
	return (NULL);
}

static size_t	ft_strlen(char *string)
{
	static const char	*last_char_in_string;

	if (!string)
		return (0x0);
	last_char_in_string = string;
	while (*last_char_in_string)
		last_char_in_string++;
	return (last_char_in_string - string);
}

char	*ft_strncat(char *dest, const char *src, int size)
{
	int	i;
	int	len;

	len = ft_strlen(dest);
	i = 0;
	while (src[i] && i < size)
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}

char	*join_and_extend_line(char *line, const char *buf, int len)
{
	char	*new_line;
	int		total_len;

	total_len = ft_strlen(line) + len;
	new_line = malloc(sizeof(char) * (total_len + 1));
	if (!new_line)
		return (NULL);
	new_line[0] = '\0';
	ft_strncat(new_line, line, ft_strlen(line));
	ft_strncat(new_line, buf, len);
	free(line);
	return (new_line);
}

void	update_buffer(char *buf, int start_index)
{
	int	i;

	i = 0;
	while (buf[start_index])
	{
		buf[i] = buf[start_index];
		i++;
		start_index++;
	}
	buf[i] = '\0';
}

char	*read_line(int fd, char *line, char *buf)
{
	int		bytes_read;
	int		i;

	bytes_read = 0;
	while (!ft_strchr(line, '\n'))
	{
		if (!ft_strlen(buf))
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				free(line);
				return (NULL);
			}
			if (bytes_read == 0)
				return (line);
			buf[bytes_read] = '\0';
		}
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		line = join_and_extend_line(line, buf, i + (buf[i] == '\n'));
		update_buffer(buf, i + (buf[i] == '\n'));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {'\0'};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	line = read_line(fd, line, buf);
	if (!line || ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>

int	main(int argc, char const *argv[])
{
	if (argc > 3)
		return (0);
	int		fd;
	int		i;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	/* test invalid file descriptor, stdin*/
	if (argc == 3)
	{
		fd = atoi(argv[2]);
		printf("fd: %d\n", fd);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		// printf("\nline: |%s|\n", line);
		printf("%d: ", i);
		printf("%s", line);

		if (line == NULL)
			break ;
		free(line);
		i++;
		/* test if still reachable (memory)*/
		// if (i == 2)
		// 	break ;
	}
	close(fd);
	return (1);
}
