/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
/*   Updated: 2023/10/31 17:06:57 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	freebuff(char *str)
{
	free(str);
	str = NULL;
}

int	checkbuffer(char *wholebuff)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(wholebuff);
	while (wholebuff[i] != '\0')
	{
		if (wholebuff[i] == '\n' || i >= length)
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*removeline(char *wholebuff, char *line)
{
	int	length;
	char	*temp;
	char	*newwholebuff;

	newwholebuff = "";
	length = checkbuffer(line);
	if (wholebuff != NULL)
	{
		temp = ft_strdup(&wholebuff[length]);
		free(wholebuff);
		newwholebuff = ft_strcat(newwholebuff, temp, ft_strlen(temp));
		free(temp);
	}
	return (newwholebuff);
}

char	*nextline(int fd, char *buffer, char **wholebuff)
{
	int	bytesread;
	char	*line;
	char	*temp;

	line = "";
	bytesread = 1;
	if (!*wholebuff)
		*wholebuff = ft_strdup("");
	while (checkbuffer(*wholebuff) == 0 && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			break;
		buffer[bytesread] = '\0';
		temp = *wholebuff;
		*wholebuff = ft_strcat(*wholebuff, buffer, BUFFER_SIZE);
		free(temp);
	}
	if (bytesread < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (checkbuffer(*wholebuff) > 0)
	{
		line = ft_strcat(line, *wholebuff, checkbuffer(*wholebuff));
		free(buffer);
	}
	else
	{
		line = ft_strdup(*wholebuff);
		if (!buffer[0])
		{
			free(*wholebuff);
			*wholebuff = ft_strdup("");
		}
		free(buffer);
	}
	return (line);
}

char 	*get_next_line(int fd)
{
	char	*buffer;
	static char	*wholebuff;
	char 	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = nextline(fd, buffer, &wholebuff);
	// if (!*wholebuff)
	if (!line || !*line)
	{
		free(wholebuff);
		wholebuff = NULL;
		free(line);
		return (NULL);
	}
	wholebuff = removeline(wholebuff, line);
	return (line);
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
/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
//	int	i = 0;
	int fd = open("test.txt", O_RDONLY);
	
//	while ((line = get_next_line(fd)) != NULL && i < 3)
//	{
//		printf("%s\n", line);
//		free(line);
//		i++;
//	}

	line = get_next_line(fd);
	printf("%s", line);
	free(line);	
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);

	printf("%s", line);
	free(line);
	
	close(fd);
	return (0);
}
*/
