/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:03:10 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/17 22:47:31 by gicomlan         ###   ########.fr       */
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

char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	static size_t	index;

	index = 0x0;
	while (index < n && source[index] != '\0')
	{
		destination[index] = source[index];
		index++;
	}
	// Si la taille de la source est inférieure à n, remplir le reste avec des '\0'
	while (index < n)
	{
		destination[index] = '\0';
		index++;
	}
	return (destination);
}

static char	*ft_strdup(const char *string)
{
	size_t	length_source;
	char	*duplicate;

	if (!string)
		return (NULL);
	length_source = ft_strlen((char *)string);
	duplicate = (char *)malloc(sizeof(char) * (length_source + 0x1));
	if (!duplicate)
		return NULL;
	ft_strncpy(duplicate, string, length_source);
	duplicate[length_source] = '\0';
	return (duplicate);
}

static char	*ft_strjoin(char *string_1, char *string_2)
{
	char	*joined_strings;
	size_t	length_string_1;
	size_t	length_string_2;

	if (!string_1 || !string_2)
	{
		free(string_1);
		return (NULL);
	}
	length_string_1 = ft_strlen(string_1);
	length_string_2 = ft_strlen(string_2);

	joined_strings = (char *)malloc(sizeof(char) * (length_string_1 + length_string_2 + 1)); // +1 pour '\0'
	if (!joined_strings)
	{
		free(string_1);
		return (NULL);
	}

	ft_strncpy(joined_strings, string_1, length_string_1);
	ft_strncpy(joined_strings + length_string_1, string_2, length_string_2);

	// S'assurer que la chaîne jointe est terminée par '\0'
	joined_strings[length_string_1 + length_string_2] = '\0';

	free(string_1);
	return (joined_strings);
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
		buffer[bytes_read] = '\0';  // Assurer la terminaison par '\0' après chaque lecture
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
			ft_strncpy(buffer, new_line_in_line + 0x1, \
				ft_strlen(new_line_in_line + 0x1));
			buffer[ft_strlen(new_line_in_line + 0x1)] = '\0';  // Terminate the string
		}
		else
			buffer[0x0] = '\0';  // Clear buffer if nothing follows the newline
		*new_line_in_line = '\0';  // Terminate the line at the newline character
	}
	else
		buffer[0x0] = '\0';  // Clear the buffer if no newline found
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*new_line_in_line;
	static char	buffer[BUFFER_SIZE + 0x1];  // Ensure space for null-terminator

	line = NULL;
	new_line_in_line = NULL;

	if (fd < 0x0 || BUFFER_SIZE <= 0x0)
		return NULL;
	line = ft_strdup(buffer);  // Start with the remaining buffer content
	line = ft_read_line(fd, line, buffer);
	if (!line)
		return NULL;
	new_line_in_line = ft_strchr(line, '\n');
	ft_update_buffer_and_line(buffer, new_line_in_line);
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
		printf("\n");
		if (line == NULL)
			break ;
		free(line);
		i++;
		/* test if still reachable (memory)*/
		// if (i == 2)
		// 	break ;
	}
	close(fd);
}

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	int		line_count;

// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <filename>\n", argv[0]);
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file %s\n", argv[1]);
// 		return (1);
// 	}
// 	line_count = 0;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line %d: %s\n", ++line_count, line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
