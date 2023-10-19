/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:19:28 by ting              #+#    #+#             */
/*   Updated: 2023/10/19 20:33:18 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat(char *s1, char *s2, int size)
{
	char	*string;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (string == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j < size)
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	free(s2);
	return (string);
}

int	isnewline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	return (i + 1);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	while (src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s1[] = "helloworld";
	char	s2[] = "byenow\nhihi";

//	printf("%d", isnewline(s2));
//	printf("%s", ft_strcat(s1, s2));
//	printf("%d", ft_strlen(s1));
//	printf("%s", ft_strdup(s1));
}
*/
