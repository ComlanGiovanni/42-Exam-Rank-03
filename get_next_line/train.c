/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:09:55 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/21 00:25:23 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

char	*ft_strdup(char *str)
{
	int		length;
	int		index;
	char	*dup;

	length = ft_strlen(str);
	index = -1;
	dup = malloc(length + 1);
	if (!dup)
		return (NULL);
	while (str[++index])
		dup[index] = str[index];
	dup[index] = 0;
	return (dup);
}

char	*get_next_line(int fd)
{
	char	buffer;
	char	rtn[7000000];
	int		n;
	int		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	index = 0;
	n = read(fd, &buffer, 1);
	while (n > 0)
	{
		rtn[index++] = buffer;
		if (buffer == '\n')
			break ;
		n = read(fd, &buffer, 1);
	}
	rtn[index] = 0;
	if (n <= 0 && index == 0)
		return (0);
	return (ft_strdup(rtn));
}
