/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:45:08 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/24 13:43:19 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 5

static size_t ft_strlen(const char *string)
{
	if (!string)
		return 0;
	size_t len = 0;
	while (string[len])
		len++;
	return len;
}

static size_t sp_strchr(char *string, char character)
{
	size_t len = 0;
	while (string[len])
	{
		if (string[len] == character)
			return (len);
		len++;
	}
	return (len);
}

static void ft_memcpy(char *destination, char *source, size_t len)
{
	size_t index = 0;
	while (index < len)
	{
		destination[index] = source[index];
		index++;
	}
}

static char *ft_strdup(char *source)
{
	size_t length_source = ft_strlen(source);
	char * duplicate = (char *)malloc(length_source + 1);
	if (duplicate == NULL)
		return (NULL);
	ft_memcpy(duplicate, source, length_source + 1);
	return (duplicate);
}

static	char *sp_join(char *line, char *buffer)
{
	if (!buffer[0])
		return line;
	size_t len1 = ft_strlen(line);
	size_t len2 = sp_strchr(buffer, '\n') + 1;
	char * dest = malloc(len1 + len2 + 1);
	if (!dest)
		return NULL;
	ft_memcpy(dest, line, len1);
	ft_memcpy(dest + len1, buffer, len2);
	if (line)
		free(line);
	dest[len1 + len2] = '\0';
	return dest;
}

char	*get_next_line(int fd)
{
	static	char buffer[BUFFER_SIZE + 1] = "\0";
	char *line = NULL;
	size_t bytes_read = 1;

	if (fd < 0 || BUFFER_SIZE < 1)
		return NULL;
	while (bytes_read)
	{
		if (buffer[0])
		{
			size_t len = sp_strchr(buffer, '\n');
			if (buffer[len] == '\n')
			{
				line = sp_join(line, buffer);
				ft_memcpy(buffer, buffer + len + 1, ft_strlen(buffer + len +1) + 1);
				return line;
			}
			else
			{
				line = sp_join(line, buffer);
				buffer[0] = '\0';
			}
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	buffer[0] = '\0';
	return (line);
}

int print_line(int fd)
{
	char *line = get_next_line(fd);
	printf("%s#", line);
	if (line)
		free(line);
	return (line != NULL);
}

#include <fcntl.h>
int	main()
{
	int fd = open("out.c", O_RDONLY);
	while (print_line(fd))
	{}
	close(fd);
	return 0;
}
