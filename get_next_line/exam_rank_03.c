/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam_rank_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:58:03 by gicomlan          #+#    #+#             */
/*   Updated: 2024/09/25 15:24:10 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // For EXIT_SUCCESS, malloc, free, atoi
#include <unistd.h> // For write, STDOUT_FILENO, read, stddef -> ssize_t NULL
#include <sys/types.h> // man 2 open to get the include and the flags for open
#include <sys/stat.h> // man 2 open to get the include and the flags for open
#include <fcntl.h> // man 2 open to get the include and the flags for open
#include <stdio.h> // For printf and perror
#include <stdarg.h> // For va_lis, va_start, va_arg, va_copy, va_end
#include <stdint.h> // For intmax_t uintmax_t
#include <limits.h> // For INT_MAX INT_MIN UINT_MAX
#include <stdbool.h> // For true false booleen

//#define BUFFER_SIZE 42 // put it in command and compile with -D BUFFER_SIZE=xx
size_t	ft_strlen(char *string)
{
	const char	*last_char_in_string;

	if (!string)
		return (0x0);
	last_char_in_string = string;
	while (*last_char_in_string)
		last_char_in_string++;
	return (last_char_in_string - string);
}

// static void	ft_put_string(char *string, int *total_length_write)
// {
// 	size_t	string_length;

// 	if (!string)
// 		string = "(null)";
// 	string_length = ft_strlen(string);
// 	*total_length_write += write(STDOUT_FILENO, string, string_length);
// }

// static void ft_put_digit(intmax_t digit, int base, int *total_length_write)
// {
// 	char *hexadecimal;

// 	hexadecimal = "0123456789abcdef";
// 	if (digit < 0x0)
// 	{
// 		*total_length_write += write(STDOUT_FILENO, "-", sizeof(char));
// 		digit = -digit;
// 	}
// 	if (digit >= base)
// 		ft_put_digit((digit / base), base, total_length_write);
// 	*total_length_write += write(STDOUT_FILENO, &hexadecimal[digit % base], sizeof(char));
// }

// static void ft_put_unsigned(uintmax_t digit, int base, int *total_length_write)
// {
// 	char *hexadecimal;

// 	hexadecimal = "0123456789abcdef";
// 	if (digit >= (uintmax_t)base)
// 		ft_put_unsigned((digit / base), base, total_length_write);
// 	*total_length_write += write(STDOUT_FILENO, &hexadecimal[digit % base], sizeof(char));
// }

// static void	ft_handle_format(const char *format, va_list arguments_pointer, int *total_length_write)
// {
// 	if (*format == '%')
// 		ft_put_string("%", total_length_write);
// 	else if (*format == 's')
// 		ft_put_string(va_arg(arguments_pointer, char *), total_length_write);
// 	else if (*format == 'd')
// 		ft_put_digit(va_arg(arguments_pointer, int), 10, total_length_write);
// 	else if (*format == 'x')
// 		ft_put_unsigned(va_arg(arguments_pointer, unsigned int), 16, total_length_write);
// }

// static int	ft_strcmp(char *s1, char *s2)
// {
// 	while (*s1++ == *s2++)
// 		if (!*s1 && !*s2)
// 			return (0x0);
// 	return (*--s1 - *--s2);
// }

char	*ft_strchr(char *string, int character)
{
	while (*string)
	{
		if (*string == (char)character)
			return (string);
		string++;
	}
	return (NULL);
}

char	*ft_strcpy(char *destination, char *source)
{
	char	*destination_copy;

	destination_copy = destination;
	while (*source)
	{
		*destination_copy = *source;
		destination_copy++;
		source++;
	}
	*destination_copy = '\0';
	return (destination);
}

// static char	*ft_strcpy(char *destination, char *source)
// {
// 	static size_t	index = 0x0;

// 	while (source[index] != '\0')
// 	{
// 		destination[index] = source[index];
// 		index++;
// 	}
// 	destination[index] = '\0';
// 	return (destination);
// }

// duplicate_string = NULL;
// length_source = 0x0;
// if (!source)
// 	return (NULL);

// duplicate = NULL;
// length_source = 0x0;
char	*ft_strdup(char *source)
{
	size_t	length_source;
	char	*duplicate_string;

	// duplicate = NULL;
	// length_source = 0x0;
	length_source = ft_strlen(source);
	duplicate_string = (char *)malloc(sizeof(char) * (length_source + 0x1));
	if (duplicate_string == NULL)
		return (NULL);
	ft_strcpy(duplicate_string, source);
	return (duplicate_string);
}

	char	*joined_line_and_buffer;
	// length_line = 0x0;
	// length_buffer = 0x0;
	// joined_line_and_buffer = NULL;

char	*ft_join_line_and_buffer(char *string_1, char *string_2)
{
	char	*joined_line_and_buffer;
	size_t	length_string_1;
	size_t	length_string_2;

	if (!string_1 || !string_2)
	{
		free(string_1);
		return (NULL);
	}
	length_string_1 = ft_strlen(string_1);
	length_string_2 = ft_strlen(string_2);
	joined_line_and_buffer = (char *)malloc(sizeof(char) * \
		((length_string_1 + length_string_2) + 0x1));
	if (!joined_line_and_buffer)
	{
		free(string_1);
		return (NULL);
	}
	ft_strcpy(joined_line_and_buffer, string_1);
	ft_strcpy(joined_line_and_buffer + length_string_1, string_2);
	free(string_1);
	return (joined_line_and_buffer);
}

void	ft_update_buffer_and_line(char *buffer, char *new_line_in_line)
{
	if (new_line_in_line)
	{
		ft_strcpy(buffer, new_line_in_line + 0x1);
		*(new_line_in_line + 0x1) = '\0';
	}
	else
		buffer[0x0] = '\0';
}

char	*ft_read_line(int fd, char *line, char *buffer)
{
	ssize_t	bytes_read;
	char	*new_line_in_line;

	bytes_read = 0x0;
	new_line_in_line = NULL;
	while (!new_line_in_line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0x0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_join_line_and_buffer(line, buffer);
		new_line_in_line = ft_strchr(line, '\n');
	}
	if (!line || ft_strlen(line) == 0x0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

//= {'\0'};
// line = NULL;
// new_line_in_line = NULL;
char	*get_next_line(int fd)
{
	char		*line;
	char		*new_line_in_line;
	static char	buffer[BUFFER_SIZE + 0x1];

	if ((fd < 0x0) || (BUFFER_SIZE <= 0x0))
		return (NULL);
	line = ft_strdup(buffer);
	line = ft_read_line(fd, line, buffer);
	if (!line)
		return (NULL);
	new_line_in_line = ft_strchr(line, '\n');
	ft_update_buffer_and_line(buffer, new_line_in_line);
	return (line);
}

// static int	ft_printf(const char *format, ...)
// {
// 	int		total_length_write;
// 	va_list	arguments_pointer;

// 	total_length_write = 0x0;
// 	va_start(arguments_pointer, format);
// 	while (*format)
// 	{
// 		if ((*format == '%') && *(format + 0x1))
// 		{
// 			format++;
// 			ft_handle_format(format, arguments_pointer, &total_length_write);
// 		}
// 		else
// 			total_length_write += write(STDOUT_FILENO, format, sizeof(char));
// 		format++;
// 	}
// 	va_end(arguments_pointer);
// 	return (total_length_write);
// }

// static int	ft_open_file(char *filename)
// {
// 	int	file_descriptor;

// 	file_descriptor = open(filename, O_RDONLY);
// 	if (file_descriptor == -1)
// 	{
// 		perror("Error while opening file");
// 		return (-1);
// 	}
// 	return (file_descriptor);
// }

// static void	ft_read_and_print_lines(int file_descriptor)
// {
// 	char	*line;
// 	int		index;
// 	int		reading;

// 	index = 0x0;
// 	reading = 0x1;
// 	line = NULL;
// 	while (reading)
// 	{
// 		line = get_next_line(file_descriptor);
// 		if (line == NULL)
// 			break ;
// 		// if (ft_strcmp(line, "exit\n") == 0x0 || ft_strcmp(line, "exit") == 0x0)
// 		// {
// 		// 	free(line);
// 		// 	break ;
// 		// }
// 		ft_printf("%s", line);
// 		free(line);
// 		index++;
// 	}
// 	ft_printf("\n-------------------------------\n");
// 	ft_printf("\nPrinting file complete.\n");
// 	ft_printf("\n------------------------------- \n");
// }

// // static void	ft_test_specific_file(char *string)
// // {
// // 	int	file_descriptor;

// // 	ft_printf("\nTesting %s :\n", string);
// // 	file_descriptor = ft_open_file(string);
// // 	if (file_descriptor == -1)
// // 	{
// // 		ft_printf("Failed to open %s file.\n", string);
// // 		return ;
// // 	}
// // 	ft_read_and_print_lines(file_descriptor);
// // 	close(file_descriptor);
// // }

// // static void	ft_string_tests(void)
// // {
// // 	int	return_ft_printf;
// // 	int	return_printf;

// // 	printf("Test 1: Simple string\n");
// // 	return_ft_printf = ft_printf("Hello, World!\n");
// // 	return_printf = printf("Hello, World!\n");
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // 	printf("Test 2: String with %%s specifier\n");
// // 	return_ft_printf = ft_printf("This is a %s.\n", "string");
// // 	return_printf = printf("This is a %s.\n", "string");
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // }

// // static void	ft_numeric_tests(void)
// // {
// // 	int	return_ft_printf;
// // 	int	return_printf;

// // 	printf("Test 3: Integer with %%d specifier\n");
// // 	return_ft_printf = ft_printf("The answer is %d.\n", 42);
// // 	return_printf = printf("The answer is %d.\n", 42);
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // 	printf("Test 4: Hexadecimal with %%x specifier\n");
// // 	return_ft_printf = ft_printf("The value is %x.\n", 255);
// // 	return_printf = printf("The value is %x.\n", 255);
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // 	printf("Test 5: Multiple specifiers\n");
// // 	return_ft_printf = ft_printf("String: %s, Integer: %d, Hex: %x\n", \
// // 			"test", 123, 0xabc);
// // 	return_printf = printf("String: %s, Integer: %d, Hex: %x\n", \
// // 			"test", 123, 0xabc);
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // }

// // static void	ft_special_cases(void)
// // {
// // 	int		return_ft_printf;
// // 	int		return_printf;
// // 	char	*null_string;

// // 	null_string = NULL;
// // 	printf("Test 6: Null string\n");
// // 	return_ft_printf = ft_printf("Null string: %s\n", null_string);
// // 	return_printf = printf("Null string: %s\n", null_string);
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // 	printf("Test 7: Percent sign\n");
// // 	return_ft_printf = ft_printf("Print a percent sign: %%\n");
// // 	return_printf = printf("Print a percent sign: %%\n");
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // }

// // static void	ft_edge_case_tests(void)
// // {
// // 	int	return_ft_printf;
// // 	int	return_printf;

// // 	printf("Test 8: Maximum and minimum integers\n");
// // 	return_ft_printf = ft_printf("INT_MAX: %d, INT_MIN: %d\n", \
// // 			INT_MAX, INT_MIN);
// // 	return_printf = printf("INT_MAX: %d, INT_MIN: %d\n", \
// // 			INT_MAX, INT_MIN);
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // 	printf("Test 9: UINT_MAX with %%x\n");
// // 	return_ft_printf = ft_printf("UINT_MAX in hex: %x\n", UINT_MAX);
// // 	return_printf = printf("UINT_MAX in hex: %x\n", UINT_MAX);
// // 	printf("Return values -> ft_printf: %d, printf: %d\n\n", \
// // 			return_ft_printf, return_printf);
// // }

// // static void	ft_check_ft_printf(void)
// // {
// // 	ft_printf("Testing ft_printf Started.\n");
// // 	ft_string_tests();
// // 	ft_numeric_tests();
// // 	ft_special_cases();
// // 	ft_edge_case_tests();
// // 	ft_printf("Testing ft_printf complete.\n");
// // }
// /**
//  * @brief
//  *
//  * clear && clang -o exam.out -D BUFFER_SIZE=1 exam_rank_03.c &&
//  * valgrind
//  * --leak-check=full
//  * --show-leak-kinds=all
//  * --track-fds=yes
//  * --show-reachable=yes
//  * --track-origins=yes
//  * ./exam.out
//  *
//  * @param argc
//  * @param argv
//  * @return int
//  */
// int	main(int argc, char **argv)
// {
// 	int	file_descriptor;

// 	(void) argc;
// 	ft_printf("\n\n\n\n\n");
// 	//ft_check_ft_printf();
// 	// if (argc > 0x2)
// 	// {
// 	// 	ft_printf("Usage: %s <filename>\n", argv[0x0]);
// 	// 	return (EXIT_FAILURE);
// 	// }
// 	//else if (argc == 0x1)
// 	//	file_descriptor = STDIN_FILENO;
// 	//else
// 	//{
// 		file_descriptor = ft_open_file(argv[1]);
// 		if (file_descriptor == -1)
// 			return (EXIT_FAILURE);
// 	//}
// 	ft_read_and_print_lines(file_descriptor);
// 	//if (file_descriptor != STDIN_FILENO)
// 		close(file_descriptor);
// 	//ft_test_specific_file("this_file_doest_exit.txt");
// 	//ft_test_specific_file("exam.out");
// 	return (EXIT_SUCCESS);
// }


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     line_count = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }

    close(fd);
    return 0;
}
