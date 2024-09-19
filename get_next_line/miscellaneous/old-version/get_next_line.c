/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:10:03 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 13:00:56 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // For read
#include <stdlib.h> // For malloc && free

/*#define BUFFER_SIZE 8192*/

char	*get_next_line(int fd)
{
	int		index;
	int		bytes;
	char	*buffer;
	char	character;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	index = 0;
	bytes = read(fd, &character, 1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (bytes > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (index == 0))
		return (free(buffer), NULL);
	buffer[index] = '\0';
	return (buffer);
}
