/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:00:08 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 11:16:21 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_str_length(char *string)
{
	int	index;

	index = 0;
	while (string[index] != '\0')
		index++;
	return (index);
}

char	*ft_str_duplicate(char *string)
{
	int		index;
	int		length;
	char	*duplicate;

	length = ft_str_length(string);
	index = 0;
	duplicate = (char *)malloc(sizeof(char) * length + 1);
	if (!duplicate)
		return (NULL);
	while (string[index] != '\0')
	{
		duplicate[index] = string[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}

char	*get_next_line(int fd)
{
	int		n;
	int		index;
	char	character;
	char	buffer[7000000];

	index = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	n = read(fd, &character, 1);
	while (n > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
		n = read(fd, &character, 1);
	}
	if (n <= 0 && index == 0)
		return (NULL);
	buffer[index] = '\0';
	return (ft_str_duplicate(buffer));
}
