/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:25:38 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/21 13:08:16 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

# define BUFFER_SIZE 42

size_t ft_strlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return p - s;
}

char *ft_strchr(const char *s, int c) {
    while (*s && *s != (char)c) s++;
    return (*s == (char)c || c == '\0') ? (char *)s : NULL;
}

char *ft_strcpy(char *d, const char *s) {
    char *p = d;
    while ((*p++ = *s++));
    return d;
}

char *ft_strdup(const char *s) {
    if (!s) return NULL;
    char *d = malloc(ft_strlen(s) + 1);
    return d ? ft_strcpy(d, s) : NULL;
}

static char *ft_join_line_and_buffer(char *str_one, char *str_two)
{
	char	*join;

	if (!str_one || !str_two)
		return (free(str_one), NULL);
	if (!(join = (char *)malloc(sizeof(char) * \
		(ft_strlen(str_one) + ft_strlen(str_two)) + 0x1)))
		return (free(str_one), NULL);
	ft_strcpy(join, str_one);
	ft_strcpy((join + ft_strlen(str_one)), str_two);
	return (free(str_one), join);
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

static char	*ft_read_line(int fd, char *line, char *buff)
{
	ssize_t	bytes_read;
	char	*new_line_in_line;

	bytes_read = 0x0;
	new_line_in_line = NULL;
	while (!(new_line_in_line = ft_strchr(line, '\n')))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buff[bytes_read] = '\0';
		line = ft_join_line_and_buffer(line, buff);
	}
	if (!line || ft_strlen(line) == 0x0)
		return (free(line), NULL);
	return (line);
}

static char	*get_next_line(int fd)
{
	char		*line;
	char		*new_line_in_line;
	static char	buffer[BUFFER_SIZE + 0x1] = {'\0'};

	line = NULL;
	new_line_in_line = NULL;
	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (NULL);
	line = ft_strdup(buffer);
	if (!(line = ft_read_line(fd, line, buffer)))
		return (NULL);
	new_line_in_line = ft_strchr(line, '\n');
	ft_update_buffer_and_line(buffer, new_line_in_line);
	return (line);
}

static int	ft_open_file(char *filename)
{
	int	file_descriptor;

	file_descriptor = open(filename, O_RDONLY);
	if (file_descriptor == -1)
	{
		perror("Error while opening file");
		return (-1);
	}
	return (file_descriptor);
}

static void	ft_read_and_print_lines(int file_descriptor)
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
	printf("\n-------------------------------\n");
	printf("\nPrinting file complete.\n");
	printf("\n------------------------------- \n");
}

static void	ft_test_specific_file(char *string)
{
	int	file_descriptor;

	printf("\nTesting %s :\n", string);
	file_descriptor = ft_open_file(string);
	if (file_descriptor == -1)
	{
		printf("Failed to open %s file.\n", string);
		return ;
	}
	ft_read_and_print_lines(file_descriptor);
	close(file_descriptor);
}

/**
 * @brief
 *
 * clear && clang -o exam.out -D BUFFER_SIZE=1 exam_rank_03.c &&
 * valgrind
 * --leak-check=full
 * --show-leak-kinds=all
 * --track-fds=yes
 * --show-reachable=yes
 * --track-origins=yes
 * ./exam.out
 *
 * @param argc
 * @param argv
 * @return int
 */
int	main(int argc, char **argv)
{
	int	file_descriptor;

	if (argc > 0x2)
	{
		printf("Usage: %s <filename>\n", argv[0x0]);
		return (EXIT_FAILURE);
	}
	else if (argc == 0x1)
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
	ft_test_specific_file("this_file_doest_exit.txt");
	ft_test_specific_file("exam.out");
	return (EXIT_SUCCESS);
}
