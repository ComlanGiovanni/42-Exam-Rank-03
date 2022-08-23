/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:33:41 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 11:12:25 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void    ft_putnbr(unsigned dig, unsigned len, char *sign, int *g_var)
{
    if (dig >= len)
        ft_putnbr(dig / len, len, sign, g_var);
    *g_var += (int)write (1, &sign[dig % len], 1);
}
void    ft_dig(long dig, int len, char *sign, int *g_var)
{
    (dig < 0) ? (*g_var += (int)write(1, "-", 1), \
    ft_putnbr(-dig, len, sign,g_var)) : ft_putnbr(dig, len, sign, g_var);
}
ssize_t ft_putstr(char *str, int len)
{
    while (str && str[len] && ++len);
    return (str ? write(1, str, len) : write(1, "(null)", 6));
}
int ft_printf(const char *fmt, ...)
{
    int     g_var = 0;
    va_list ap;
    va_start(ap, fmt);
    while (*fmt)
    {
        if (*fmt == '%' && *(fmt + 1) == 's' && (fmt += 2))
            g_var += (int)ft_putstr(va_arg(ap, char *), 0);
        else if (*fmt == '%' && *(fmt + 1) == 'x' && (fmt += 2))
            ft_putnbr(va_arg(ap, int), 16, "0123456789abcdef", &g_var);
        else if (*fmt == '%' && *(fmt + 1) == 'd' && (fmt += 2))
            ft_dig(va_arg(ap, int), 10, "0123456789", &g_var);
        else
            g_var += (int)write(1, fmt++, 1);
    }
    return (va_end(ap), g_var);
}

/*
#include <stdarg.h>
#include <unistd.h>

void    ft_put_number(unsigned digits, unsigned length, char *sign, int *len)
{
    if (digits >= length)
		ft_put_number(digits / length, length, sign, len);
    *len += (int)write (1, &sign[digits % length], 1);
}

void    ft_digits(long digits, int length, char *sign, int *len)
{
    (digits < 0) ? (*len += (int)write(1, "-", 1), \
    ft_put_number(-digits, length, sign,len)) : ft_put_number(digits, length, sign, len);
}

size_t	ft_put_string(char *string, int length)
{
	while (string && string[length] && ++length);
	return (string ? write(1, string, length) : write(1, "(null)", 6));
}

int	ft_printf(const char *format, ...)
{
	int		len = 0;
	va_list	ptr;

	va_start(ptr, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's' && (format += 2))
			len += (int)ft_put_string(va_arg(ptr, char *), 0);
		else if (*format == '%' && *(format + 1) == 'x' && (format += 2))
			ft_put_number(va_arg(ptr, int), 16, "0123456789abcdef", &len);
		else if (*format == '%' && *(format + 1) == 'd' && (format += 2))
			ft_digits(va_arg(ptr, int), 10, "0123456789", &len);
		else
			len += (int)write(1, format++, 1);
	}
	return (va_end(ptr), len);
}
*/
