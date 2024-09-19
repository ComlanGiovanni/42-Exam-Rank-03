/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:03:10 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/19 22:53:00 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // For write, STDOUT_FILENO, read
#include <stdlib.h> // For EXIT_SUCCESS, malloc, free

//#define BUFFER_SIZE 42

size_t ft_strlen(char *string)
{
    const char *last_char_in_string;

    if (!string)
        return 0;
    last_char_in_string = string;
    while (*last_char_in_string)
        last_char_in_string++;
    return (last_char_in_string - string);
}

char *ft_strchr(char *string, int character)
{
    while (*string)
    {
        if (*string == (char)character)
            return string;
        string++;
    }
    return NULL;
}

char *ft_strcpy(char *destination, char *source)
{
    char *destination_copy;

    destination_copy = destination;
    while (*source)
    {
        *destination_copy = *source;
        destination_copy++;
        source++;
    }
    *destination_copy = '\0';
    return destination;
}

char *ft_strdup(char *string)
{
    size_t length_source;
    char *duplicate;

    length_source = ft_strlen(string);
    duplicate = (char *)malloc(sizeof(char) * (length_source + 1));
    if (duplicate == NULL)
        return NULL;
    ft_strcpy(duplicate, string);
    return duplicate;
}

char *ft_strjoin(char *string_1, char *string_2)
{
    char *joined_strings;
    size_t length_string_1;
    size_t length_string_2;

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
    ft_strcpy(joined_strings, string_1);
    ft_strcpy(joined_strings + length_string_1, string_2);
    free(string_1);
    return joined_strings;
}

char *ft_read_line(int fd, char *line, char *buffer)
{
    ssize_t bytes_read;
    char *new_line_in_line;

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

void ft_update_buffer_and_line(char *buffer, char *new_line_in_line)
{
    if (new_line_in_line)
    {
        ft_strcpy(buffer, new_line_in_line + 1);
        *(new_line_in_line + 1) = '\0';
    }
    else
    {
        buffer[0] = '\0';
    }
}

char *get_next_line(int fd)
{
    char *line;
    char *new_line_in_line;
    static char buffer[BUFFER_SIZE + 1];

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    line = ft_strdup(buffer);
    line = ft_read_line(fd, line, buffer);
    if (!line)
        return NULL;
    new_line_in_line = ft_strchr(line, '\n');
    ft_update_buffer_and_line(buffer, new_line_in_line);
    return line;
}

// Include your main function and other includes here

/*
cc -o gnl -Wall -Werror -Wextra -D BUFFER_SIZE=88 get_next_line.c && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --show-reachable=yes --track-origins=yes ./gnl get_next_line.c
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    if (argc > 3)
        return (0);
    int     fd;
    int     i;
    char    *line;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
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
        printf("%d: ", i);
        if (line == NULL)
        {
            printf("(null)\n");
            break ;
        }
        printf("%s", line);
        free(line);
        i++;
    }
    if (fd >= 0)
        close(fd);
    return (1);
}
