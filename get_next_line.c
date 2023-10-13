/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/09 13:28:24 by ting             ###   ########.fr       */
=======
/*   Updated: 2023/10/10 18:19:49 by ting             ###   ########.fr       */
>>>>>>> 4c31cb58ffc585373fa755cfb6763f36a757ecf0
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	j;
	int	i;
	int	checker;
	char	*buffer;
	char	line[700000];

	j = 0;
	i = 0;
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	checker = read(fd, buffer, BUFFER_SIZE);
	while (BUFFER_SIZE > 0 && checker > 0)
	{
		line[i] = buffer[j];
		i++;
		j++;
		if (buffer[j] == '\n')
		{
			j++;
			break;
		}
	}
	line[i] = '\0';
	if (checker <= 0 && j == 0)
	{
		return (NULL);
	}
	return (ft_strdup(line));
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;

	int fd = open("test.txt", O_RDWR);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}

