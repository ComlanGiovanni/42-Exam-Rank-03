/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:54 by gicomlan          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:56 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

static void ft_put(uintmax_t n, int base, int *len, char *set)
{
    if (n >= (uintmax_t)base)
        ft_put(n / base, base, len, set);
    *len += write(1, &set[n % base], 1);
}

int ft_printf(const char *fmt, ...)
{
    va_list ap;
    int len = 0;
    char *s;
    uintmax_t u;
    intmax_t d;

    va_start(ap, fmt);
    while (*fmt)
    {
        if (*fmt == '%' && *(++fmt))
        {
            if (*fmt == 's')
            {
                s = va_arg(ap, char*);
                len += write(1, s ? s : "(null)", s ? __builtin_strlen(s) : 6);
            }
            else if (*fmt == 'd')
            {
                d = va_arg(ap, int);
                if (d < 0) { len += write(1, "-", 1); d = -d; }
                ft_put(d, 10, &len, "0123456789");
            }
            else if (*fmt == 'x')
                ft_put(va_arg(ap, unsigned int), 16, &len, "0123456789abcdef");
            else
                len += write(1, fmt, 1);
        }
        else
            len += write(1, fmt, 1);
        fmt++;
    }
    va_end(ap);
    return len;
}
