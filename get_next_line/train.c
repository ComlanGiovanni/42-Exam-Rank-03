/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:58:03 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/20 09:29:44 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // For EXIT_SUCCESS, malloc, free, atoi
#include <unistd.h> // For write, STDOUT_FILENO, read, stddef -> ssize_t NULL

//#define BUFFER_SIZE 42 // put it in command and compile with -D BUFFER_SIZE=xx

// man 2 open to get the include and the flags for open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //For printf
#include <string.h> // For strcmp
#include <stdbool.h>

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

// bad idea to manage a NULL string because
// if we return NULL we can nor free and i guess
// we are going to free a NULL pointer
// if (!string)
// return (NULL);
static char	*ft_strdup(char *string)
{
	size_t	length_source;
	char	*duplicate;

	length_source = 0x0;
	duplicate = NULL;
	length_source = ft_strlen(string);
	duplicate = (char *)malloc(sizeof(char) * (length_source + 0x1));
	if (duplicate == NULL)
		return (NULL);
	ft_strcpy(duplicate, string);
	return (duplicate);
}

static char	*ft_strjoin(char *string_one, char *string_two)
{
	char	*joined_strings;
	size_t	length_string_one;
	size_t	length_string_two;

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

static	char	*ft_read_line(int fd, char *line, char *buffer)
{
	ssize_t	bytes_read;
	char	*new_line_in_line;

	bytes_read = 0x0;
	new_line_in_line = NULL;
	while (!new_line_in_line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0x0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
		new_line_in_line = ft_strchr(line, '\n');
	}
	if (!line || ft_strlen(line) == 0x0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

//buffer[0x0] = '\0';
char	*get_next_line(int fd)
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

//printf("%d: ", index); to get the line number
//printf("(null)\n"); only to check for /dev/null
//check /dev/urandom
//open a file that doesn't not exist
int	ft_open_file(char *filename)
{
	int file_descriptor;

	file_descriptor = open(filename, O_RDONLY);
	if (file_descriptor == -1)
	{
		perror("Error while opening file");
		return (-1);
	}
	return (file_descriptor);
}

void	ft_read_and_print_lines(int file_descriptor)
{
	char	*line;
	int		index;
	int		reading;

	index = 0x0;
	reading = 0x1;
	while (reading)
	{
		line = get_next_line(file_descriptor);
		if (line == NULL)
			break ;
		if (strcmp(line, "exit\n") == 0x0 || strcmp(line, "exit") == 0x0)
		{
			free(line);
			break ;
		}
		printf("%s", line);
		free(line);
		index++;
	}
}

int	main(int argc, char **argv)
{
	int	file_descriptor;

	if (argc > 0x2)
	{
		printf("Usage: %s <filename>\n", argv[0x0]);
		return (EXIT_FAILURE);
	}
	if (argc == 0x1)
		file_descriptor = STDIN_FILENO;
	else
	{
		file_descriptor = ft_open_file(argv[1]);
		if (file_descriptor == -1)
			return (EXIT_FAILURE);
	}
	ft_read_and_print_lines(file_descriptor);
	if (file_descriptor != STDIN_FILENO)
		close(file_descriptor);
	return (EXIT_SUCCESS);
}
