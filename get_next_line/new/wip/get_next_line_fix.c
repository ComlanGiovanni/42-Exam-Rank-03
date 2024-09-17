/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_fix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:03:10 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/17 18:00:47 by gicomlan         ###   ########.fr       */
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

// static char	*ft_strcpy(char *destination, char *source)
// {
// 	static char	*destination_copy;

// 	destination_copy = destination;
// 	while (*source)
// 	{
// 		*destination_copy = *source;
// 		destination_copy++;
// 		source++;
// 	}
// 	*destination_copy = '\0';
// 	return (destination);
// }

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

static char	 __attribute__((unused)) *ft_strdup(char *string)
{
	size_t	length_source;
	char	*duplicate;

	length_source = ft_strlen(string);
	duplicate = (char *)malloc(sizeof(char) * (length_source + 0x1));
	if (duplicate == NULL)
		return (NULL);
	duplicate = ft_strcpy(duplicate, string);
	return (duplicate);
}

static	char	*ft_strjoin(char *string_1, char *string_2)
{
	char	*joined_strings;
	size_t	length_string_1;
	size_t	length_string_2;

	if (!string_1 || !string_2)
	{
		free(string_1);
		return (NULL);
	}
	joined_strings = NULL;
	length_string_1 = ft_strlen(string_1);
	length_string_2 = ft_strlen(string_2);
	joined_strings = (char *)malloc(sizeof(char) \
		* ((length_string_1 + length_string_2) + 0x1));
	if (!joined_strings)
	{
		free(string_1);
		return (NULL);
	}
	ft_strcpy(joined_strings, string_1);
	ft_strcpy((joined_strings + length_string_1), string_2);
	free(string_1);
	return (joined_strings);
}

static char	 __attribute__((unused))  *ft_read_line(int fd, char *line, char *buffer)
{
	ssize_t		bytes_read;
	char		*new_line_in_line;

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
	if (!line || (ft_strlen(line) == 0x0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static void  __attribute__((unused))  ft_update_buffer_and_line(char *buffer, char *new_line_in_line)
{
    if (new_line_in_line)
    {
        size_t remaining_len = ft_strlen(new_line_in_line + 1);
        if (remaining_len > 0) {
            ft_strcpy(buffer, new_line_in_line + 1);
        } else {
            buffer[0] = '\0';
        }
        *(new_line_in_line + 1) = '\0';
    }
    else
    {
        buffer[0] = '\0';
    }
}

char *get_next_line(int fd)
{
    char        *line;
    char        *new_line_in_line;
    static char buffer[BUFFER_SIZE + 1];
    static int  buffer_pos = 0;
    static int  buffer_len = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    line = NULL;
    while (1)
    {
        if (buffer_pos >= buffer_len)
        {
            buffer_len = read(fd, buffer, BUFFER_SIZE);
            if (buffer_len <= 0)
                break;
            buffer_pos = 0;
            buffer[buffer_len] = '\0';
        }

        new_line_in_line = ft_strchr(buffer + buffer_pos, '\n');
        if (new_line_in_line)
        {
            *new_line_in_line = '\0';
            line = ft_strjoin(line, buffer + buffer_pos);
            buffer_pos = (new_line_in_line - buffer) + 1;
            return (line);
        }
        else
        {
            line = ft_strjoin(line, buffer + buffer_pos);
            buffer_pos = buffer_len;
        }
    }

    return (line);
}

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file %s\n", argv[1]);
		return (1);
	}
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s\n", ++line_count, line);
		free(line);
	}
	close(fd);
	return (0);
}
