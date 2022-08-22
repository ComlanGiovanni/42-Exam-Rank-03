/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:42:39 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/22 14:26:53 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char *get_next_line(int fd)
{
	int rd = 0;
	char c;
	char *buffer = malloc(101010);
	int i = 0;

	while((rd = read(fd, &c, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
	{
		buffer[i] = c;
		if (buffer[i] == '\n')
		{
			buffer[i + 1] = '\0';
			return (buffer);
		}
		i++;
	}
	if (rd == -1 || i == 0 || (!rd && !buffer[i - 1]))
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return(buffer);
}
*/

/*
int main()
{
	int fd;
	char *s;

	fd = open("myfile.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s != NULL)
	{
		printf("%s", s);
		s = get_next_line(fd);
	}
	return (0);
}
*/

/*
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	int rd = 0;
	char	c;
	if ((rd = read(fd, &c, 1)) == 0)
		return (NULL);
	char	*line = malloc(100000);
	char	*word = line;
	*line++ = c;
	while ((rd = read(fd, &c, 1)) > 0 && c != '\n')
		*line++ = c;
	if (c == '\n')
		*line++ = '\n';
	*line = '\0';
	return (word);
}
*/

/*
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    int 	i = 0;
    int 	rd = 0;
    char	character;
    char 	*buffer = malloc(10000);

    while ((rd = read(fd, &character, 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] =  '\0';
    return(buffer);
}
*/

/*
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char *s = malloc(10000), *c = s;
    while (read(fd, c, 1) > 0 && *c++ != '\n');
    return c > s ? (*c = 0, s) : (free(s), NULL);
}
*/
