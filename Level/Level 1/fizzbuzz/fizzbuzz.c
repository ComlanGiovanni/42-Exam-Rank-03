/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:07:12 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/05 16:51:07 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		ft_putchar(str[idx]);
		idx++;
	}
}

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

void	ft_nbr(int number)
{
	if (number > 9)
		ft_nbr(number / 10);
	ft_putchar("0123456789"[number % 10]);
}

int	main(void)
{
	int	number;

	number = 1;
	while (number <= 100)
	{
		if (((number % 3) == 0) && ((number % 5) == 0))
			ft_putstr("fizzbuzz");
		else if ((number % 3) == 0)
			ft_putstr("fizz");
		else if ((number % 5) == 0)
			ft_putstr("buzz");
		else
			ft_nbr(number);
		ft_putchar('\n');
		number++;
	}
	return (0);
}
