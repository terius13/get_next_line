/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
/*   Updated: 2023/10/24 22:02:52 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
char	removeline(char *wholebuff)
{
	
}
*/

int	checkbuffer(char *wholebuff)
{
	int	i;

	i = 0;

	while (wholebuff != NULL && wholebuff[i] != '\0')
	{
		if (wholebuff[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}

	return (0);
}

char	*nextline(int fd, char *buffer, char *wholebuff)
{
	int	bytesread;
	int	pos;
	char	*line;//need to malloc line

	line = "";
	pos= 0;
	if (!wholebuff)
		wholebuff = ft_strdup("");
	while ((pos = checkbuffer(wholebuff)) == 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		buffer[bytesread] = '\0';
		wholebuff = ft_strcat(wholebuff, buffer, BUFFER_SIZE);
	}
	if (pos > 0)
	{
		line = ft_strcat(line, wholebuff, pos);
	}
	return (line);
}

char 	*get_next_line(int fd)
{
	char	*buffer;
	static char	*wholebuff;
	char 	*line;
	int	newlinepos;

	line = "";
	newlinepos = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	wholebuff = (char *)malloc(BUFFER_SIZE + 1 + ft_strlen(wholebuff));
	line = nextline(fd, buffer, wholebuff);
//	wholebuff = removeline(line);
	return (line);

	//read until there is a newline stop reading when it see a new line
}

/*
char	*get_next_line(int fd)
{
	char	*buffer;
	static char	*wholebuff;
	int	checker;
	int	i;
	char	*line;
	char	*temp;

	i = 0;
	checker = 1;
	line = "";
	//malloc everything
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	// malloc should change to calloc or bzero to not get garbage value
	if (wholebuff[i] != '\0')
	{
		wholebuff += isnewline(wholebuff);
	}
	//create a helper function for this
	while (checker > 0)
	{
		checker = read(fd, buffer, BUFFER_SIZE);
		buffer[checker] = '\0';
		if (!wholebuff && checker > 0)
			wholebuff = ft_strdup("");
		temp = ft_strdup(wholebuff);
		free(wholebuff);
		wholebuff = ft_strcat(temp, buffer, ft_strlen(buffer));
		free(temp);
		while (1)
		{
			if (wholebuff[i] == '\n' || wholebuff[i] == '\0')
			{
				temp = ft_strdup(wholebuff);
				line = ft_strcat(line, temp, i);
				break;
			}
			else if (wholebuff[i] != '\n' && isnewline(wholebuff) > BUFFER_SIZE)
			{
				checker = read(fd, buffer, BUFFER_SIZE);
				temp = ft_strdup(wholebuff);
				free(wholebuff);
				wholebuff = ft_strcat(temp, buffer, ft_strlen(buffer));
				free(temp);
				wholebuff[ft_strlen(wholebuff)] = '\0';
			}
			i++;
		}
		break;
	}
	i++;	
	if (wholebuff[i] == '\0')
	{
		free(wholebuff);
	}
	return (line);
}
*/
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
	char	*line;
//	int	i = 0;
	int fd = open("test.txt", O_RDWR);
	
//	while ((line = get_next_line(fd)) != NULL && i < 3)
//	{
//		printf("%s\n", line);
//		free(line);
//		i++;
//	}

	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	/*
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("%s\n", line);
	*/
	free(line);
	close(fd);
	return (0);
}

