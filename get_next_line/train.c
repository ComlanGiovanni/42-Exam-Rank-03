/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:42:39 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 01:20:26 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

/*#define BUFFER_SIZE 1*/

char	*get_next_line(int fd)
{
	int		byte;
	int		index;
	char	character;
	char	*buffer;

	byte = 0;
	index = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	byte = read(fd, &character, 1);
	while (byte > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
		byte = read(fd, &character, 1);
	}
	if (byte <= 0 && index == 0)
		return (free(buffer), NULL);
	buffer[index] = '\0';
	return (buffer);
}

/*

#include <stdarg.h>

void	put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	put_digit(long long int nbr, int base, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		put_digit((nbr / base), base, len);
	*len += write(1, &hexa[nbr % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int			len;
	va_list		ptr;

	len = 0;
	va_start(ptr, format);
	while (*format)
	{
		if ((*format == '%') && *(format + 1))
		{
			format++;
			if (*format == 's')
				put_str(va_arg(ptr, char *), &len);
			else if (*format == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &len);
			else if (*format == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (va_end(ptr), len);
}

*/

#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	int		line;
	char	*string;

	line = 1;
	string = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		string = get_next_line(fd);
		while (string != NULL)
		{
			ft_printf("Line %d - %s ", line, string);
			string = get_next_line(fd);
			line++;
		}
		if (!string)
			printf("Line %d - (null) EOF", line);
		close(fd);
	}
	return (0);
}

//gcc -Wall -Werror -Wextra train.c -D BUFFER_SIZE=10 && ./a.out train.c
