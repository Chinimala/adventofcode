/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day5_part2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 19:01:13 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/07 16:26:50 by aalleman    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int		values[100000];
char	b[10000];

void	do_it(int previous_output)
{
	int		i;
	int		value1;
	int		value2;
	char	b[100];
	int		ret;

	i = 2;
	while (values[i] != 99)
	{
		if ((values[i] / 100) % 10 == 0)
			value1 = values[values[i + 1]];
		else
			value1 = values[i + 1];
		if ((values[i] / 1000) % 10 == 0)
			value2 = values[values[i + 2]];
		else
			value2 = values[i + 2];
		if (values[i] % 100 == 1)
		{
			values[values[i + 3]] = value1 + value2;
			i += 4;
		}
		else if (values[i] % 100 == 2)
		{
			values[values[i + 3]] = value1 * value2;
			i += 4;
		}
		else if (values[i] % 100 == 3)
		{
			//dprintf(1, "Input : \n");
			//ret = read(0, b, 100);
			values[values[i + 1]] = previous_output;
			i += 2;
		}
		else if (values[i] % 100 == 4)
		{
			//printf("\nOutput : %d\n", value1);
			printf("%d", value1);
			i += 2;
		}
		else if (values[i] % 100 == 5)
		{
			if (value1)
				i = value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 6)
		{
			if (!value1)
				i = value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 7)
		{
			if (value1 < value2)
				values[values[i + 3]] = 1;
			else
				values[values[i + 3]] = 0;
			i += 4;
		}
		else if (values[i] % 100 == 8)
		{
			if (value1 == value2)
				values[values[i + 3]] = 1;
			else
				values[values[i + 3]] = 0;
			i += 4;
		}
	}
}

int		main(int ac, char **av)
{
	char			*buffer = b;
	int				i;
	int				fd;
	char			c;

	if (ac != 3 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 10000);
	i = 0;
	while (*buffer != '\n')
	{
		values[i++] = atoi(buffer);
		while (isdigit(*buffer) || *buffer == '-')
			buffer++;
		if (*buffer == ',')
			buffer++;
	}
	read(0, &c, 1);
	values[values[1]] = c - '0';
	do_it(atoi(av[2]));
	return(0);
}
