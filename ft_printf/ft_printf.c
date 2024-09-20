/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:44:34 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/20 09:44:36 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h> // For va_lis, va_start, va_arg, va_copy, va_end
#include <unistd.h> // For malloc, free, write
#include <stdint.h>  // Pour intmax_t
#include <stdbool.h> // Pour true and false

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
		number = -(intmax_t)number;
		*length += write(STDOUT_FILENO, "-", sizeof(char));
	}
	if (number >= (uintmax_t)base)
		ft_put_digit((number / base), base, length, false);
	*length += write(STDOUT_FILENO, &hexadecimal[number % base], sizeof(char));
}

static void	ft_handle_format(const char *format, va_list arguments, int *length)
{
	if (*format == '%')
		ft_put_string("%", length);
	else if (*format == 's')
		ft_put_string(va_arg(arguments, char *), length);
	else if (*format == 'd')
		ft_put_digit((intmax_t)va_arg(arguments, int), \
			DECIMAL_BASE, length, true);
	else if (*format == 'x')
		ft_put_digit(va_arg(arguments, unsigned int), \
			HEXADECIMAL_BASE, length, false);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list	arguments;

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
