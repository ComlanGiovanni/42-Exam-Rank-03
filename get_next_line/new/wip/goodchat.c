#include "get_next_linee.h"

static int	ft_append(char *s, char *buffer)
{
	int	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	int j = 0;
	while (buffer[j])
	{
		s[i] = buffer[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (1);
}

static int	get_len(char *s)
{
	int i = 0;
	if (!s || !*s)
		return (-1);
	while (s[i] && s[i] != '\n')
	{
		i++;
	}
	if (s[i] == '\n')
		return (i + 1);
	else
		return (i);
}

static void	ft_strcpy(char *s, char *src, int len)
{
	int i = 0;
	while (i < len)
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
}

static void	ft_memmove(char *s, int len)
{
	int	i = 0;
	while (s[len + i])
	{
		s[i] = s[len + i];
		i++;
	}
	s[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*content;
	static int	i = 0;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	int			len;
	int			bytes;

	if (i < 0)
		return (NULL);
	i++;
	if (i == 1)
	{
		content = malloc(10000000);
		content[0] = '\0';
		while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
		{
			buffer[bytes] = '\0';
			ft_append(content, buffer);
		}
	}
	len = get_len(content);
	if (len < 0)
	{
		free(content);
		i = -1;
		return (NULL);
	}
	line = malloc(len + 1);
	ft_strcpy(line, content, len);
	ft_memmove(content, len);
	return (line);
}

int	main(void)
{
	int fd = open("main.c", O_RDONLY);

	for (int i = 0; i < 42; i++)
	{
		char *s = get_next_line(fd);
		printf("%d: %s", i, s);
		free(s);
	}

	return (0);
}
