/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:59:59 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 11:08:28 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
