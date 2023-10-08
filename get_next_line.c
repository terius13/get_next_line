/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
/*   Updated: 2023/10/08 23:43:38 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int	j;
	int	checker;
	char	buffer;
	char	*line;

	j = 0;
	checker = 1;
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!line)
	{
		free(line);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	checker = read(fd, &buffer, 1);
	while (BUFFER_SIZE > 0 && checker > 0)
	{
		line[j] = buffer;
		j++;
		if (buffer == '\n')
			break;
		checker = read(fd, &buffer, 1);
	}
	line[j] = '\0';
	if (checker <= 0 && j == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("test.txt", O_RDWR);
	printf("%s", get_next_line(fd));
}
*/
