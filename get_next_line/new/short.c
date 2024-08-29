/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:55:22 by gicomlan          #+#    #+#             */
/*   Updated: 2024/08/29 12:11:57 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char *line = NULL, *tmp;
    int r = 0, len = 0, nl_pos = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (!buf[nl_pos])
        {
            r = read(fd, buf, BUFFER_SIZE);
            if (r <= 0 && !len)
                return (free(line), NULL);
            buf[r] = '\0';
            nl_pos = 0;
        }
        while (buf[nl_pos] && buf[nl_pos] != '\n')
            nl_pos++;
        tmp = malloc(len + nl_pos + 2);
        if (!tmp)
            return (free(line), NULL);
        for (int i = 0; i < len; i++)
            tmp[i] = line[i];
        for (int i = 0; i < nl_pos + (buf[nl_pos] == '\n'); i++)
            tmp[len + i] = buf[i];
        tmp[len + nl_pos + (buf[nl_pos] == '\n')] = '\0';
        free(line);
        line = tmp;
        len += nl_pos + (buf[nl_pos] == '\n');
        if (buf[nl_pos] == '\n')
        {
            for (int i = 0; i <= BUFFER_SIZE - nl_pos; i++)
                buf[i] = buf[nl_pos + 1 + i];
            return (line);
        }
        buf[0] = '\0';
    }
}
