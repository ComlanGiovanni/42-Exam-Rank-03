/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:58:03 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/19 10:07:36 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //write NULL
#include <stdlib.h>

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

void	ft_update_buffer(char *buffer, int start_index)
{
	static index;

	index = 0x0;
	while (buffer[start_index])
	{
		buffer[index] = buffer[start_index];
		index++;
		start_index++;
	}
	buffer[index] = '\0';
}

char	*ft_join_and_extend_line(char *line, const char *buffer, int length)
{
	char *new_line;
	static int	total_length;

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

static	char *ft_read_line(int fd, char *line, char *buffer)
{
	static int		index;
	static int		bytes_read;

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

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 0x1] = {'\0'};
	char		*line;

	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (NULL);
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0x0] = '\0';
	line = ft_read_line(fd, line, buffer);
	if (!line || (ft_strlen(line) == 0x0))
	{
		free(line);
		return (NULL);
	}
	return (line);

}
