/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:25:38 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/20 12:54:51 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

# define BUFFER_SIZE 42


static size_t	ft_strlen(char *string)
{
	const char	*last_char_in_string;

	if (!string)
		return (0x0);
	last_char_in_string = string;
	while (*last_char_in_string)
		last_char_in_string++;
	return (last_char_in_string - string);
}

static char	*ft_strchr(char *string, int character)
{
	while (*string)
	{
		if (*string == (char)character)
			return (string);
		string++;
	}
	return (NULL);
}

static char	*ft_strcpy(char *destination, char *source)
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

static char	*ft_strdup(char *string)
{
	char	*duplicate_string;
	size_t	length_source_string;

	length_source_string = 0x0;
	duplicate_string = NULL;
	if (!string)
		return (NULL);
	length_source_string = ft_strlen(string);
	duplicate_string = (char *)malloc(sizeof(char) * \
		(length_source_string + 0x1));
	if (duplicate_string == NULL)
		return (NULL);
	ft_strcpy(duplicate_string, string);
	return (duplicate_string);
}

static char *ft_join_line_and_buffer(char *string_one, char *string_two)
{
	char *joined_strings;
	size_t length_string_one;
	size_t length_string_two;

	if (!string_one || !string_two)
	{
		free(string_one);
		return (NULL);
	}
	length_string_one = ft_strlen(string_one);
	length_string_two = ft_strlen(string_two);
	joined_strings = (char *)malloc(sizeof(char) * \
		((length_string_one + length_string_two) + 0x1));
	if (!joined_strings)
	{
		free(string_one);
		return (NULL);
	}
	ft_strcpy(joined_strings, string_one);
	ft_strcpy((joined_strings + length_string_one), string_two);
	free(string_one);
	return (joined_strings);
}

static char *ft_read_line(int file_descriptor, char *line, char *buffer)
{
	ssize_t	bytes_read;
	char	*new_line_in_line;

	bytes_read = 0x0;
	new_line_in_line = NULL;
	while (!new_line_in_line) // && line ??
	{
		bytes_read = read(file_descriptor, buffer, BUFFER_SIZE);
		if (bytes_read <= 0x0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_join_line_and_buffer(line, buffer);
		new_line_in_line = ft_strchr(line, '\n');
	}
	if (!line || ft_strlen(line) == 0x0)
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
		ft_strcpy(buffer, (new_line_in_line + 0x1));
		*(new_line_in_line + 0x1) = '\0';
	}
	else
		buffer[0x0] = '\0';
}

static char *get_next_line(int fd)
{
	char		*line;
	char		*new_line_in_line;
	static char	buffer[BUFFER_SIZE + 0x1] = {'\0'};

	line = NULL;
	new_line_in_line = NULL;
	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (NULL);
	line = ft_strdup(buffer);
	line = ft_read_line(fd, line, buffer);
	if (!line)
		return (NULL);
	new_line_in_line = ft_strchr(line, '\n');
	ft_update_buffer_and_line(buffer, new_line_in_line);
	return (line);
}
