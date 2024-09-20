/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:35:55 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/20 11:05:11 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

static size_t	ft_strlen(char *string)
{
	const char	*last_char_in_string;

	if (!string)
		return (0x0);
	last_char_in_string = string;
	while (*last_char_in_string)
		last_char_in_string++;
	return (last_char_in_string - string);
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
		ft_put_digit((__intmax_t)va_arg(arguments, int), \
			0xa, length, true);
	else if (*format == 'x')
		ft_put_digit(va_arg(arguments, unsigned int), \
			0x10, length, false);
}

static int	ft_printf(const char *format, ...)
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

static void	ft_string_tests(void)
{
	int	return_ft_printf;
	int	return_printf;

	printf("Test 1: Simple string\n");
	return_ft_printf = ft_printf("Hello, World!\n");
	return_printf = printf("Hello, World!\n");
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 2: String with %%s specifier\n");
	return_ft_printf = ft_printf("This is a %s.\n", "string");
	return_printf = printf("This is a %s.\n", "string");
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_numeric_tests(void)
{
	int	return_ft_printf;
	int	return_printf;

	printf("Test 3: Integer with %%d specifier\n");
	return_ft_printf = ft_printf("The answer is %d.\n", 42);
	return_printf = printf("The answer is %d.\n", 42);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 4: Hexadecimal with %%x specifier\n");
	return_ft_printf = ft_printf("The value is %x.\n", 255);
	return_printf = printf("The value is %x.\n", 255);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 5: Multiple specifiers\n");
	return_ft_printf = ft_printf("String: %s, Integer: %d, Hex: %x\n", \
			"test", 123, 0xabc);
	return_printf = printf("String: %s, Integer: %d, Hex: %x\n", \
			"test", 123, 0xabc);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_special_cases(void)
{
	int		return_ft_printf;
	int		return_printf;
	char	*null_string;

	null_string = NULL;
	printf("Test 6: Null string\n");
	return_ft_printf = ft_printf("Null string: %s\n", null_string);
	return_printf = printf("Null string: %s\n", null_string);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 7: Percent sign\n");
	return_ft_printf = ft_printf("Print a percent sign: %%\n");
	return_printf = printf("Print a percent sign: %%\n");
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_edge_case_tests(void)
{
	int	return_ft_printf;
	int	return_printf;

	printf("Test 8: Maximum and minimum integers\n");
	return_ft_printf = ft_printf("INT_MAX: %d, INT_MIN: %d\n", \
			INT_MAX, INT_MIN);
	return_printf = printf("INT_MAX: %d, INT_MIN: %d\n", \
			INT_MAX, INT_MIN);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
	printf("Test 9: UINT_MAX with %%x\n");
	return_ft_printf = ft_printf("UINT_MAX in hex: %x\n", UINT_MAX);
	return_printf = printf("UINT_MAX in hex: %x\n", UINT_MAX);
	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
			return_ft_printf, return_printf);
}

static void	ft_check_ft_printf(void)
{
	ft_printf("Testing ft_printf Started.\n");
	ft_string_tests();
	ft_numeric_tests();
	ft_special_cases();
	ft_edge_case_tests();
	ft_printf("Testing ft_printf complete.\n");
}

int	main(int argc, char **argv)
{
	ft_check_ft_printf();
	return (EXIT_SUCCESS);
}
