/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:04 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/17 23:18:47 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h> //For write STDOUT_FILENO read
# include <stdlib.h> //For EXIT_SUCCESS malloc free

# define BUFFER_SIZE 42

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
	int	index;
	int	length;

	length = ft_strlen(dest);
	index = 0x0;
	while (src[index] && (index < size))
	{
		dest[length + index] = src[index];
		index++;
	}
	dest[length + index] = '\0';
	return (dest);
}

char	*ft_join_and_extend_line(char *line, const char *buffer, int length)
{
	char	*new_line;
	int		total_length;

	total_length = ft_strlen(line) + length;
	new_line = (char *)malloc(sizeof(char) * (total_length + 0x1));
	if (!new_line)
		return (NULL);
	new_line[0x0] = '\0';
	ft_strncat(new_line, line, ft_strlen(line));
	ft_strncat(new_line, buffer, length);
	free(line);
	return (new_line);
}

void	ft_update_buffer(char *buf, int start_index)
{
	int	index;

	index = 0x0;
	while (buf[start_index])
	{
		buf[index] = buf[start_index];
		index++;
		start_index++;
	}
	buf[index] = '\0';
}

char	*ft_read_line(int fd, char *line, char *buffer)
{
	int		index;
	int		bytes_read;

	bytes_read = 0x0;
	index = 0x0;
	while (!ft_strchr(line, '\n'))
	{
		if (!ft_strlen(buffer))
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0x0)
			{
				free(line);
				return (NULL);
			}
			if (bytes_read == 0x0)
				return (line);
			buffer[bytes_read] = '\0';
		}
		while (buffer[index] && buffer[index] != '\n')
			index++;
		line = ft_join_and_extend_line(line, buffer, index + (buffer[index] == '\n'));
		ft_update_buffer(buffer, index + (buffer[index] == '\n'));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {'\0'};
	char		*line;

	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (NULL);
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0x0] = '\0';
	line = ft_read_line(fd, line, buf);
	if (!line || (ft_strlen(line) == 0x0))
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
