/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:00:14 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/22 23:30:09 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	int		n;
	int		index;
	char	character;
	char	*buffer = (char *)malloc(sizeof(char) * 10000);

	index = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
        return (free(buffer), NULL);
	while ((n = read(fd, &character, 1)) > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
	}
	if (n <= 0 && index == 0)
		return (free(buffer), NULL);
	buffer[index] = '\0';
	return (buffer);
}
