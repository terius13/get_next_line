/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
/*   Updated: 2023/11/08 18:11:40 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_buffer(int *bytesread, int fd, char *wholebuff)
{
	char	*buffer;
	char	*temp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!wholebuff)
	{
		wholebuff = (char *)malloc(BUFFER_SIZE + 1);
		ft_bzero(wholebuff, BUFFER_SIZE + 1);
	}
	*bytesread = read(fd, buffer, BUFFER_SIZE);
	temp = wholebuff;
	wholebuff = ft_strcat(temp, buffer, ft_strlen(buffer));
	free(temp);
	free(buffer);
	if (*bytesread < 0 || (!*bytesread && !*wholebuff))
	{
		free(wholebuff);
		wholebuff = NULL;
	}
	return (wholebuff);
}

static char	*next_line(char *wholebuff)
{
	char	*line;
	int		len;
	char	*ptr;

	len = 0;
	while (wholebuff[len] != '\n')
		len++;
	len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	ft_bzero(line, len);
	ptr = line;
	line = ft_strcat(ptr, wholebuff, len);
	free(ptr);
	return (line);
}

static char	*removeline(char *wholebuff)
{
	int		len;
	char	*ptr;

	len = 0;
	while (wholebuff[len] != '\n')
		len++;
	len++;
	ptr = wholebuff;
	wholebuff = ft_strdup(ft_strchr(wholebuff, '\n') + 1);
	free(ptr);
	if (wholebuff[0] == '\0')
	{
		free(wholebuff);
		wholebuff = NULL;
	}
	return (wholebuff);
}

char	*get_next_line(int fd)
{
	static char	*wholebuff;
	char		*line;
	int			bytesread;

	bytesread = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(wholebuff, '\n') == NULL && bytesread)
	{
		wholebuff = get_buffer(&bytesread, fd, wholebuff);
		if (!wholebuff)
			break ;
	}
	if (ft_strchr(wholebuff, '\n') != NULL)
	{
		line = next_line(wholebuff);
		wholebuff = removeline(wholebuff);
		return (line);
	}
	if (!wholebuff)
		return (NULL);
	line = ft_strdup(wholebuff);
	free(wholebuff);
	wholebuff = NULL;
	return (line);
}

/*
int	checkbuffer(char *wholebuff)
{
	int	i;
//	int	length;

	i = 0;
	while (wholebuff[i] && wholebuff[i] != '\n')
		i++;
	if (wholebuff[i] == 0)
	{
	//	free(wholebuff);
		return (0);
	}
	if (wholebuff[i] == '\n')
		i++;
	return (i);
}

char	*getbuffer(int fd, char *wholebuff)
{
	char	*buffer;
	int	bytesread;

	bytesread = 1;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0 || checkbuffer(buffer) == 0)
		{
			free(wholebuff);
			wholebuff = NULL;
			free(buffer);
			return (NULL);
		}
		if (bytesread == 0)
			break;
		buffer[bytesread] = '\0';
		if (!wholebuff)
			wholebuff = '\0';
		wholebuff = ft_strcat(wholebuff, buffer, ft_strlen(buffer));
		if (checkbuffer(buffer) > 0)
			break;
	}
	free(buffer);
	return (wholebuff);
}

char	*nextline(char *wholebuff)
{
	char	*line;
	int	pos;

	line = "";
	pos = checkbuffer(wholebuff);
	line = ft_strcat(line, wholebuff, pos);
	return (line);
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

char	*get_next_line(int fd)
{
	static char	*wholebuff;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	wholebuff = getbuffer(fd, wholebuff);
	if (!wholebuff)
		return (NULL);
	line = nextline(wholebuff);
	wholebuff = removeline(wholebuff, line);
	return (line);
}
*/
/*
char	*nextline(int fd, char *buffer, char **wholebuff)
{
	int	bytesread;
	char	*temp;
	int	pos;
	char	*line;

	line = "";
	bytesread = 1;
	pos = 0;
	while (bytesread != 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (0);
		else if(bytesread == 0)
			break;
		buffer[bytesread] = '\0';
		if (!*wholebuff)
			*wholebuff = ft_strdup("");
		temp = *wholebuff;
		*wholebuff = ft_strcat(temp, buffer, ft_strlen(buffer));//Size might be wrong
		free(temp);
		temp = NULL;
		if (checkbuffer(buffer) > 0)
		{
			break;
		}
	}
	if ((pos = checkbuffer(*wholebuff)) > 0)
		line = ft_strcat(line, *wholebuff, pos);
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
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	line = nextline(fd, buffer, &wholebuff);
	if (!line || !*line)
	{
		free(wholebuff);
		wholebuff = NULL;
		free(buffer);
		return (NULL);
	}
	wholebuff = removeline(wholebuff, line);
	free(buffer);
	return (line);
}
*/
/*
#include <stdio.h>
#include <fcntl.h>
int     main(void)
{
        char    *line;
//      int     i = 0;
        int fd = open("test.txt", O_RDONLY);

//      while ((line = get_next_line(fd)) != NULL && i < 3)
//      {
//              printf("%s\n", line);
//              free(line);
//              i++;
//      }

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
/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
//	int	i = 0;
	int fd = open("tests/only_nl.txt", O_RDONLY);
	
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
