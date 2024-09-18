/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:58:03 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/18 18:24:50 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define BUFFER_SIZE	42

static void __attribute__((unused)) ft_putstr_fd(char *str, int fd)
{
	if (fd >= 0x0)
		while (*str)
			write(fd, str++, sizeof(char));
}

static	*ft_read_line(int fd, char *line, char *buffer)
{
	int	index;
	int	bytes_read; //size_t for read -1

	bytes_read = 0x0;
	index = 0x0;
	while (!ft_strchr(line, '\n'))
	{
		if (!ft_strlen(buffer))
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0x0)
			{
				free(line);
				return (NULL);
			}
			if (bytes_read == 0x0)
				return (line);
			buffer[bytes_read] = '\0';
		}
		while (buffer[index] && buffer[index] != '\n')
			index++;
		line = ft_join_and_extend_line(line, buffer, index + (buffer[index] == '\n'));
		ft_update_buffer(buffer, index + (buffer[index] == '\n'));
	}
	return (line);
}


char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 0x1] = {'\0'};
	char 	*line;

	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (NULL);
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0x0] = '\0';
	line = ft_read_line(fd, line, buffer);
	if(!line || (ft_strlen(line) == 0x0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
