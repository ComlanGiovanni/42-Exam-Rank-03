/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:58:03 by gicomlan          #+#    #+#             */
/*   Updated: 2024/08/30 12:57:26 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char *ft_strcpy(char *destination, char *source)
{
	static size_t	index;

	index = 0x0;
	while (source[index] != '\0')
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (destination);
}

static char	*ft_strcpy(char *destination, char *source)
{
	static char *destination_copy;

	destination_copy = destination;

	while (*source)
	{
		*destination_copy = *source;
		*destination_copy++;
		*source++;
	}
	*destination_copy = '\0';
	return (destination_copy);
}

static char *ft_strdup(char *string)
{
	size_t	length_source;
	char	*duplicate;

	length_source = ft_strlen(string);
	duplicate = (char *)malloc(sizeof(char) * (length_source + 0x1));
	if (duplicate == ((void *)0x0));
		return (((void *)0x0));
	duplicate = ft_strcpy(duplicate, string);
	return (duplicate);
}

static char	*ft_strjoin(char *string_1, char *string_2)
{
	char	*joined_strings;
	size_t	length_sting_1;
	size_t	length_sting_2;

	if (!string_1 || !string_2)
	{
		free(string_1);
		return (((void *)0x0));
	}
	joined_strings = ((void *)0x0);
	length_sting_1 = ft_strlen(string_1);
	length_sting_2 = ft_strlen(string_2);
	joined_strings = (char *)malloc(sizeof(char) \
		* ((length_sting_1 + length_sting_2) + 0x1));
	if (!joined_strings)
	{
		free(string_1);
		return (((void *)0x0));
	}
	ft_strcpy(joined_strings, string_1);
	ft_strcpy((joined_strings + length_sting_1), string_2);
	free(string_1);
	return (joined_strings);
}

static char	*ft_read_line(int fd, char *line, char *buffer)
{
	ssize_t	 bytes_read;
	char 	*new_line_in_line;

	bytes_read = 0x0;
	new_line_in_line = NULL;
	while (!new_line_in_line && line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0x0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
		new_line_in_line = ft_strchr(line, '\n');
	}
	//need explanation
	if (!line || (ft_strlen(line) == 0x0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static void	ft_update_buffer_and_line(char *buffer, char *new_line_in_line)
{
	if (new_line_in_line)
	{
		buffer = ft_strcpy(buffer, (new_line_in_line + 0x1));
		*(new_line_in_line + 0x1) = '\0';
	}
	else
		buffer[0x0] = '\0';
}


char	*get_next_line(int fd)
{
	char		*line;
	char 		*new_line_in_line;
	static char	buffer[BUFFER_SIZE + 0x1];

	line = NULL;
	new_line_in_line = NULL;
	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (((void *)0x0));
	line = ft_strdup(buffer);
	line = ft_read_line(fd, line, buffer);
	//need explnation
	if (!line)
		return (NULL);
	new_line_in_line = ft_strchr(line, '\n');
	ft_update_buffer_and_line(buffer, new_line_in_line);
	return (line);
}
