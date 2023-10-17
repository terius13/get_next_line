/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
/*   Updated: 2023/10/17 16:30:28 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char	*get_next_line(int fd)
{
	char	*buffer;
	static char	*wholebuff = "";
	int	checker;
	int	i;
	char	*line;

	i = 0;
	checker = 1;
	line = "";
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	// malloc should change to calloc or bzero to not get garbage value
	if (wholebuff[i] != '\0')
	{
		wholebuff += isnewline(wholebuff);
	}
	while (checker > 0)
	{
		checker = read(fd, buffer, BUFFER_SIZE);
		buffer[checker] = '\0';
		wholebuff = ft_strcat(wholebuff, buffer, ft_strlen(buffer));
		//need to find a way to free strcat
		while (wholebuff[i] != '\0')
		{
			if (wholebuff[i] == '\n')
			{
				line = ft_strcat(line, wholebuff, i);
				break;
			}
			else if (wholebuff[i] != '\n')
			{
				checker = read(fd, buffer, BUFFER_SIZE);
				wholebuff = ft_strcat(wholebuff, buffer, ft_strlen(buffer));
			}
			i++;
		}
		break;
	}
	if (checker <= 0 && buffer == NULL)
		return (NULL);
	// need to manually add \n to line
	return (line);
}
/*
char	*get_next_line(int fd)
{
	static int	j = 0;
	int	i;
	int	checker;
	char	*buffer;
	char	line[BUFFER_SIZE + 1];
	//use static char

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
*/

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
//	char	*line;

	int fd = open("test.txt", O_RDWR);
	/*
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	*/
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	close(fd);
	return (0);
}

