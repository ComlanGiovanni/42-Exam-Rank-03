/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:00:23 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/22 23:15:57 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char *b = (char *)malloc(sizeof(char) * 10000), *c = b;
    while (read(fd, c, 1) > 0 && *c++ != '\n');
    return c > b ? (*c = 0, b) : (free(b), NULL);
}
