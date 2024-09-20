#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strncat(char *dest, char *src, int size)
{
	int	i;
	int	len;

	len = ft_strlen(dest);
	i = -1;
	while (src[++i] && i < size)
		dest[len + i] = src[i];
	dest[len + i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {'\0'};
	char		*line = NULL;
	char		*tmp;
	int			i = 0;
	int			j;
	int			bytes = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = (char *)malloc(sizeof(char))))
		return (free(line), NULL);
	line[0] = '\0';
	while (ft_strchr(line, '\n') == NULL) {
		if (!ft_strlen(buf) && (bytes = read(fd, buf, BUFFER_SIZE)) <= 0)
			break ;
		buf[bytes] *= !(bytes > 0);
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		i += (buf[i] == '\n');
		tmp = line;
		if (!(line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + i + 1))))
			return (free(tmp), NULL);
		line[0] = '\0';
		line = ft_strncat(line, tmp, ft_strlen(tmp));
		free(tmp);
		line = ft_strncat(line, buf, i);
		j = 0;
		while (buf[i])
			buf[j++] = buf[i++];
		buf[j] = '\0';
	}
	// return (((bytes == 0 && i == 0) || bytes < 0) ? (ft_memset(buf, 0, BUFFER_SIZE), free(line), NULL) : (line));
	return ((bytes >= 0 && i != 0) ? (line) : (free(line), NULL));
}


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>

int	main(int argc, char const *argv[])
{
	if (argc > 3)
		return (0);
	int		fd;
	int		i;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	/* test invalid file descriptor, stdin*/
	if (argc == 3)
	{
		fd = atoi(argv[2]);
		printf("fd: %d\n", fd);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		// printf("\nline: |%s|\n", line);
		printf("%d: ", i);
		printf("%s", line);

		if (line == NULL)
			break ;
		free(line);
		i++;
		/* test if still reachable (memory)*/
		// if (i == 2)
		// 	break ;
	}
	close(fd);
	return (1);
}
