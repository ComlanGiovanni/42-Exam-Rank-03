/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:09:07 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/22 13:10:19 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void	ft_put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	ft_put_digit(long long nbr, int base, int *len)
{
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_put_digit((nbr / base), base, len);
	*len += write(1, &"0123456789abcdef"[nbr % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	ptr;

	len = 0;
	va_start(ptr, format);
	while (*format)
	{
		if (*format != '%')
			len += write(1, format, 1);
		else if ((*format == '%') && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_put_str(va_arg(ptr, char *), &len);
			else if (*format == 'x')
				ft_put_digit((long long)va_arg(ptr, unsigned int), 16, &len);
			else if (*format == 'd')
				ft_put_digit((long long)va_arg(ptr, int), 10, &len);
		}
		format++;
	}
	return (va_end(ptr), len);
}

/*
#include <unistd.h>
#include <stdarg.h>

int	ft_put_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_put_str(char *str)
{
	int	length;

	length = 0;
	if (!str)
		str = "(null)";
	while (*str)
		length += write(1, str++, 1);
	return (length);
}

int	ft_put_nbr(long int number)
{
	int	length;

	length = 0;
	if (number < 0)
	{
		length += write(1, "-", 1);
		number *= -1;
	}
	if (number < 10)
		length += ft_put_char(number + '0');
	else
	{
		length += ft_put_nbr(number / 10);
		length += ft_put_nbr(number % 10);
	}
	return (length);
}

int	ft_put_hexa(unsigned int hexa)
{
	int	length;

	length = 0;
	if (hexa >= 16)
	{
		length += ft_put_hexa(hexa / 16);
		length += ft_put_hexa(hexa % 16);
	}
	else if (hexa > 9)
		length += ft_put_char(hexa + 'W');
	else
		length += ft_put_char(hexa + '0');
	return (length);
}

int	ft_printf(const char *format, ...)
{
	int		index;
	int		length;
	va_list	argument;

	index = 0;
	length = 0;
	va_start(argument, format);
	while (format[index])
	{
		if (format[index] != '%')
			length += write(1, &format[index], 1);
		else if (format[index] == '%' && format[index + 1])
		{
			index++;
			if (format[index] == 's')
				length += ft_put_str(va_arg(argument, char *));
			else if (format[index] == 'x')
				length += ft_put_hexa(va_arg(argument, unsigned int));
			else if (format[index] == 'd')
				length += ft_put_nbr(va_arg(argument, int));
		}
		index++;
	}
	va_end(argument);
	return (length);
}
*/
