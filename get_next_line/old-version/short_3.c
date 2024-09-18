/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:00:17 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 11:20:17 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char *b = (char *)malloc(sizeof(char) * 10000), *y = b;
    while (read(fd, y, 1) > 0 && *y++ != '\n');
    return y > b ? (*y = 0, b) : (free(b), NULL);
}
