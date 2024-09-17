/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:03:10 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/17 18:12:06 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line.h"

static size_t	ft_strlen(char *string)
{
	size_t len = 0;
	if (!string)
		return 0;
	while (string[len] != '\0')
		len++;
	return len;
}

static char	*ft_strchr(char *string, int character)
{
	while (*string)
	{
		if (*string == (char)character)
			return string;
		string++;
	}
	return NULL;
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	// Si la taille de la source est inférieure à n, remplir le reste avec des '\0'
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return dst;
}

static char	*ft_strdup(const char *string)
{
	size_t	length_source;
	char	*duplicate;

	if (!string)
		return NULL;

	length_source = ft_strlen((char *)string);
	duplicate = (char *)malloc(sizeof(char) * (length_source + 1));
	if (!duplicate)
		return NULL;
	ft_strncpy(duplicate, string, length_source);
	duplicate[length_source] = '\0';
	return duplicate;
}

static char	*ft_strjoin(char *string_1, char *string_2)
{
	char	*joined_strings;
	size_t	length_string_1;
	size_t	length_string_2;

	if (!string_1 || !string_2)
	{
		free(string_1);
		return NULL;
	}
	length_string_1 = ft_strlen(string_1);
	length_string_2 = ft_strlen(string_2);

	joined_strings = (char *)malloc(sizeof(char) * (length_string_1 + length_string_2 + 1));
	if (!joined_strings)
	{
		free(string_1);
		return NULL;
	}

	ft_strncpy(joined_strings, string_1, length_string_1);
	ft_strncpy(joined_strings + length_string_1, string_2, length_string_2);
	joined_strings[length_string_1 + length_string_2] = '\0';

	free(string_1);
	return joined_strings;
}

static char	*ft_read_line(int fd, char *line, char *buffer)
{
	ssize_t	bytes_read;
	char	*new_line_in_line;

	bytes_read = 0;
	new_line_in_line = NULL;

	while (!new_line_in_line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
		new_line_in_line = ft_strchr(line, '\n');
	}
	if (!line || ft_strlen(line) == 0)
	{
		free(line);
		return NULL;
	}
	return line;
}

static void	ft_update_buffer_and_line(char *buffer, char *new_line_in_line)
{
	if (new_line_in_line)
	{
		if (*(new_line_in_line + 1) != '\0')
		{
		       ft_strncpy(buffer, new_line_in_line + 1, ft_strlen(new_line_in_line + 1));
			buffer[ft_strlen(new_line_in_line + 1)] = '\0';  // Terminate the string
		}
		else
		{
			buffer[0] = '\0';  // Clear buffer if nothing follows the newline
		}
		*new_line_in_line = '\0';  // Terminate the line at the newline character
	}
	else
	{
		buffer[0] = '\0';  // Clear the buffer if no newline found
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*new_line_in_line;
	static char	buffer[BUFFER_SIZE + 1];  // Ensure space for null-terminator

	line = NULL;
	new_line_in_line = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	line = ft_strdup(buffer);  // Start with the remaining buffer content
	line = ft_read_line(fd, line, buffer);

	if (!line)
		return NULL;

	new_line_in_line = ft_strchr(line, '\n');
	ft_update_buffer_and_line(buffer, new_line_in_line);
	return line;
}

