/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:09:51 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/22 12:03:43 by gcomlan          ###   ########.fr       */
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
			else if (*format == 'd')
				ft_put_digit((long long)va_arg(ptr, int), 10, &len);
			else if (*format == 'x')
				ft_put_digit((long long)va_arg(ptr, unsigned int), 16, &len);
		}
		format++;
	}
	return (va_end(ptr), len);
}

/*

% print %% ?

#include <limits.h>
#include <stdio.h>
int main()
{
    int f, s;
   f = ft_printf("%s %c %d %d %x\n",
   "hello world", 'X', INT_MAX, INT_MIN, UINT_MAX);
    s =    printf("%s %c %d %d %x\n",
	"hello world", 'X', INT_MAX, INT_MIN, UINT_MAX);
    printf("%d | %d\n", f, s);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("I - %d\n", printf("qwerty %s\t%ld\t%x\n",
"stroka1", 214714814563, -42));
// 	printf("II - %d\n", ft_printf("qwerty %s\t%d\t%x\n",
"stroka2", 214714814563, -42));
// 	return 0;
// }

#include <limits.h>
#include <stdio.h>
int main()
{
    int f, s;
   f = ft_printf("%s %c %d %d %x\n", "hello world",
   'X', INT_MAX, INT_MIN, UINT_MAX);
    s =    printf("%s %c %d %d %x\n", "hello world",
	'X', INT_MAX, INT_MIN, UINT_MAX);
    printf("%d | %d\n", f, s);
}

int main()
{
	char *ch = "(a string)";
	int	i;

	i = ft_printf("%d %d %d %d %d", -2147483647, 17, 3, 1300, -400);
	ft_printf("\n");
	ft_printf("%d", i);
	ft_printf("\n");

	i = ft_printf("%x %x %x %x %x", 0, 40, -23, -2147483647, 7);
	ft_printf("\n");
	ft_printf("%d", i);
	ft_printf("\n");

	i = ft_printf("Hello this is %s in a string", ch);
	ft_printf("\n");
	ft_printf("%d", i);
	ft_printf("\n");

	i = ft_printf("Percentages: %%");
	ft_printf("\n");
	ft_printf("%d", i);
	ft_printf("\n");

	printf("\n");
	printf("\n");

	i = printf("%d %d %d %d %d", -2147483647, 17, 3, 1300, -400);
	printf("\n");
	printf("%d", i);
	printf("\n");

	i = printf("%x %x %x %x %x", 0, 40, -23, -2147483647, 7);
	printf("\n");
	printf("%d", i);
	printf("\n");

	i = printf("Hello this is %s in a string", ch);
	printf("\n");
	printf("%d", i);
	printf("\n");

	i = printf("Percentages: %%");
	printf("\n");
	printf("%d", i);
	printf("\n");

	return (0);
}

*/
