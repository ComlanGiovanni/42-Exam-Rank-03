/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:35:55 by gicomlan          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:07 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h> // For va_lis, va_start, va_arg, va_copy, va_end
#include <unistd.h> // For malloc, free, write
#include <stdint.h>  // Pour intmax_t

#define TRUE 0x1
#define FALSE 0x0
#define DECIMAL_BASE 0xa
#define HEXADECIMAL_BASE 0x10

static size_t	ft_strlen(char *string)
{
	const char	*last_char_of_string;

	if (!string)
		return (0x0);
	last_char_of_string = string;
	while (*last_char_of_string)
		last_char_of_string++;
	return (last_char_of_string - string);
}

static void	ft_put_string(char *string, int *length)
{
	size_t	string_length;

	if (!string)
		string = "(null)";
	string_length = ft_strlen(string);
	*length += write(STDOUT_FILENO, string, string_length);
}

static void	ft_put_digit(uintmax_t number, int base, int *length, int is_signed)
{
	char	*hexadecimal;

	hexadecimal = "0123456789abcdef";
	if (is_signed && ((intmax_t)number < 0x0))
	{
		number = - (intmax_t)number;
		*length += write(STDOUT_FILENO, "-", sizeof(char));
	}
	if (number >= (uintmax_t)base)
		ft_put_digit((number / base), base, length, FALSE);
	*length += write(STDOUT_FILENO, &hexadecimal[number % base], sizeof(char));
}

static void	ft_handle_format(const char *format, va_list arguments, int *length)
{
	if (*format == '%')
		ft_put_string('%', length);
	else if (*format == 's')
		ft_put_string(va_arg(arguments, char *), length);
	else if (*format == 'd')
		ft_put_digit((intmax_t)va_arg(arguments, int), \
			DECIMAL_BASE, length, TRUE);
	else if (*format == 'x')
		ft_put_digit(va_arg(arguments, unsigned int), \
			HEXADECIMAL_BASE, length, FALSE);
}

int	ft_printf(const char *format, ...)
{
	int			length;
	va_list		arguments;

	length = 0x0;
	va_start(arguments, format);
	while (*format)
	{
		if ((*format == '%') && *(format + 0x1))
		{
			format++;
			ft_handle_format(format, arguments, &length);
		}
		else
			length += write(STDOUT_FILENO, format, sizeof(char));
		format++;
	}
	va_end(arguments);
	return (length);
}

/*
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	size;

	size = 0;
	size = ft_printf("%%\n");
	printf("%d\n", size);
	size = printf("%%\n");
	printf("%d\n", size);
	size = ft_printf("%s\n", "toto");
	printf("%d\n", size);
	size = printf("%s\n", "toto");
	printf("%d\n", size);
	size = ft_printf("Magic %s is %d\n", "number", 42);
	printf("%d\n", size);
	size = printf("Magic %s is %d\n", "number", 42);
	printf("%d\n", size);
	size = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", size);
	size = printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", size);
	size = ft_printf("%d %d %x\n", INT_MAX, INT_MIN, UINT_MAX);
	printf("%d\n", size);
	size = ft_printf("%d %d %x\n", INT_MAX, INT_MIN, UINT_MAX);
	printf("%d\n", size);
	size = ft_printf("%d, %d\n", 0, -24);
	printf("%d\n", size);
	size = ft_printf("%d, %d\n", 0, -24);
	printf("%d\n", size);
	printf("%d\n", size);
	ft_printf("Hello world %\n");
	return (0);
}
*/
