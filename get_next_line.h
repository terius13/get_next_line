/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:20:08 by ting              #+#    #+#             */
/*   Updated: 2023/10/27 15:04:20 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int	ft_strlen(char *str);
char	*ft_strcat(char *s1, char *s2, int size);
int	isnewline(char *str);
char	*ft_strdup(const char *src);
void	ft_bzero(void *s, size_t n);

#endif
