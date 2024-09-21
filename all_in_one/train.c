/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:25:38 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/21 13:09:38 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
















static int	ft_open_file(char *filename)
{
	int	file_descriptor;

	file_descriptor = open(filename, O_RDONLY);
	if (file_descriptor == -1)
	{
		perror("Error while opening file");
		return (-1);
	}
	return (file_descriptor);
}

static void	ft_read_and_print_lines(int file_descriptor)
{
	char	*line;
	int		index;
	int		reading;

	index = 0x0;
	reading = 0x1;
	while (reading)
	{
		line = get_next_line(file_descriptor);
		if (line == NULL)
			break ;
		if (strcmp(line, "exit\n") == 0x0 || strcmp(line, "exit") == 0x0)
		{
			free(line);
			break ;
		}
		printf("%s", line);
		free(line);
		index++;
	}
	printf("\n-------------------------------\n");
	printf("\nPrinting file complete.\n");
	printf("\n------------------------------- \n");
}

static void	ft_test_specific_file(char *string)
{
	int	file_descriptor;

	printf("\nTesting %s :\n", string);
	file_descriptor = ft_open_file(string);
	if (file_descriptor == -1)
	{
		printf("Failed to open %s file.\n", string);
		return ;
	}
	ft_read_and_print_lines(file_descriptor);
	close(file_descriptor);
}

/**
 * @brief
 *
 * clear && clang -o exam.out -D BUFFER_SIZE=1 exam_rank_03.c &&
 * valgrind
 * --leak-check=full
 * --show-leak-kinds=all
 * --track-fds=yes
 * --show-reachable=yes
 * --track-origins=yes
 * ./exam.out
 *
 * @param argc
 * @param argv
 * @return int
 */
int	main(int argc, char **argv)
{
	int	file_descriptor;

	if (argc > 0x2)
	{
		printf("Usage: %s <filename>\n", argv[0x0]);
		return (EXIT_FAILURE);
	}
	else if (argc == 0x1)
		file_descriptor = STDIN_FILENO;
	else
	{
		file_descriptor = ft_open_file(argv[1]);
		if (file_descriptor == -1)
			return (EXIT_FAILURE);
	}
	ft_read_and_print_lines(file_descriptor);
	if (file_descriptor != STDIN_FILENO)
		close(file_descriptor);
	ft_test_specific_file("this_file_doest_exit.txt");
	ft_test_specific_file("exam.out");
	return (EXIT_SUCCESS);
}
