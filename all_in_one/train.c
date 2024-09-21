/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:25:38 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/21 13:05:57 by gicomlan         ###   ########.fr       */
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
#define BUFFER_SIZE 42

#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE];
    static ssize_t bytes_in_buf = 0, buf_pos = 0;
    char *line = NULL;
    size_t line_len = 0, line_cap = BUFFER_SIZE;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    line = malloc(line_cap + 1);
    if (!line)
        return NULL;
    while (1)
    {
        if (buf_pos >= bytes_in_buf)
        {
            bytes_in_buf = read(fd, buf, BUFFER_SIZE);
            if (bytes_in_buf <= 0)
                break;
            buf_pos = 0;
        }
        while (buf_pos < bytes_in_buf)
        {
            char c = buf[buf_pos++];
            if (line_len >= line_cap)
            {
                char *new_line = malloc(line_cap + BUFFER_SIZE + 1);
                if (!new_line)
                {
                    free(line);
                    return NULL;
                }
                for (size_t i = 0; i < line_len; i++)
                    new_line[i] = line[i];
                free(line);
                line = new_line;
                line_cap += BUFFER_SIZE;
            }
            line[line_len++] = c;
            if (c == '\n')
                break;
        }
        if (line_len > 0 && line[line_len - 1] == '\n')
            break;
    }
    if (line_len == 0)
    {
        free(line);
        return NULL;
    }
    line[line_len] = '\0';
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
