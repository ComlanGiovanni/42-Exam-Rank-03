/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:25:38 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/21 12:57:57 by gicomlan         ###   ########.fr       */
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
    while (*s && *s != c) s++;
    return (*s == c || c == '\0') ? (char *)s : NULL;
}

char *ft_strcpy(char *d, const char *s) {
    char *p = d;
    while ((*p++ = *s++));
    return d;
}

char *ft_strdup(const char *s) {
    char *d = malloc(ft_strlen(s) + 1);
    return d ? ft_strcpy(d, s) : NULL;
}

char *ft_strjoin(char *s1, char *s2) {
    size_t len1 = ft_strlen(s1), len2 = ft_strlen(s2);
    char *join = malloc(len1 + len2 + 1);
    if (!join) return (free(s1), NULL);
    ft_strcpy(join, s1);
    ft_strcpy(join + len1, s2);
    return (free(s1), join);
}

void ft_update_buffer(char *buffer, char *newline) {
    if (newline) {
        ft_strcpy(buffer, newline + 1);
        newline[1] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

char *ft_read_line(int fd, char *line, char *buffer) {
    ssize_t bytes;
    char *newline;
    while (!(newline = ft_strchr(line, '\n'))) {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        line = ft_strjoin(line, buffer);
        if (!line) return NULL;
    }
    return (line && *line) ? line : (free(line), NULL);
}

char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1] = {0};
    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;
    char *line = ft_strdup(buffer);
    if (!line) return NULL;
    line = ft_read_line(fd, line, buffer);
    if (!line) return NULL;
    char *newline = ft_strchr(line, '\n');
    ft_update_buffer(buffer, newline);
    return line;
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
