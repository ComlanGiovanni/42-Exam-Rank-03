/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:00:11 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/17 18:38:49 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     line_count = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }

    close(fd);
    return 0;
}

// #include "get_next_line.h"

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/uio.h>
// #include <sys/types.h>

// int	main(int argc, char const *argv[])
// {
// 	if (argc > 3)
// 		return (0);
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	fd = open(argv[1], O_RDONLY);
// 	/* test invalid file descriptor, stdin*/
// 	if (argc == 3)
// 	{
// 		fd = atoi(argv[2]);
// 		printf("fd: %d\n", fd);
// 	}
// 	i = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		// printf("\nline: |%s|\n", line);
// 		printf("%d: ", i);
// 		printf("%s", line);
// 		printf("\n");
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 		i++;
// 		/* test if still reachable (memory)*/
// 		// if (i == 2)
// 		// 	break ;
// 	}
// 	close(fd);
// }
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
