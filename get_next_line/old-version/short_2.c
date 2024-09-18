/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcomlan <gcomlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:00:14 by gcomlan           #+#    #+#             */
/*   Updated: 2022/08/23 11:19:22 by gcomlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    int 	i = 0;
    int 	rd = 0;
    char	c;
    char 	*buff = malloc(10000);

    while ((rd = read(fd, &c, 1)) > 0)
    {
        buff[i++] = c;
        if (c == '\n')
            break ;
    }
    if ((!buff[i - 1] && !rd) || rd == -1)
    {
        free(buff);
        return (NULL);
    }
    buff[i] =  '\0';
    return(buff);
}
