/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:33:59 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/22 11:11:00 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	ft_put_str(char *str)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	while (*str)
		len += write(1, str++, 1);
	return (len);
}

int	ft_put_digit(long long nbr, int base)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len += write(1, "-", 1);
	}
	if (nbr >= base)
		len += ft_put_digit((nbr / base), base);
	len += write(1, &"0123456789abcdef"[nbr % base], 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		idx;
	int		len;
	va_list	arg;

	idx = 0;
	len = 0;
	va_start(arg, format);
	while (format[idx])
	{
		if (format[idx] != '%')
			len += write(1, &format[idx], 1);
		else if (format[idx] == '%' && format[idx + 1])
		{
			idx++;
			if (format[idx] == 's')
				len += ft_put_str(va_arg(arg, char *));
			else if (format[idx] == 'x')
				len += ft_put_digit((long long)va_arg(arg, unsigned int), 16);
			else if (format[idx] == 'd')
				len += ft_put_digit((long long)va_arg(arg, int), 10);
		}
		idx++;
	}
	va_end(arg);
	return (len);
}
