/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:02:09 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/25 21:03:10 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(char *string)
{
	const char	*last_char_in_string;

	if (!string)
		return (0x0);
	last_char_in_string = string;
	while (*last_char_in_string)
		last_char_in_string++;
	return (last_char_in_string - string);
}

static char	*ft_strcpy(char *destination, char *source)
{
	size_t	index = 0x0;

	while (source[index] != '\0')
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (destination);
}

char	*ft_strdup(char *source)
{
	size_t	length_source;
	char	*duplicate;

	length_source = ft_strlen(source);
	duplicate = (char *)malloc(sizeof(char) * (length_source + 0x1));
	if (!duplicate)
		return (NULL);
	ft_strcpy(duplicate, source);
	return (duplicate);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	buffer_read = 0x0;
	static int 	buffer_pos = 0x0;
	int			line_index;

	line_index = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[line_index++] = buffer[buffer_pos++];
		if (line[line_index - 1] == '\n')
			break ;
	}
	line[line_index] = '\0';
	if (line_index == 0)
		return (NULL);
	return (ft_strdup(line));
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
