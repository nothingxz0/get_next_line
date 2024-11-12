/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:38:05 by slasfar           #+#    #+#             */
/*   Updated: 2024/11/12 02:38:33 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	read_file(char *buffer, int fd)
{
	int	buffer_read;	

	buffer[BUFFER_SIZE + 1] = '\0';
	return (buffer_read = read(fd, buffer, BUFFER_SIZE));
}

int	find_new_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
	}
	return (-1);
}

void	free_ptr(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	slen;

	if (!str || start < 0 || len <= 0)
    	return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
	{
		str = (char *) malloc(1);
		if (str)
			str[0] = '\0';
		return (str);
	}
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	char	*str;

	i = 0;
	j = 0;
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	str = (char *) malloc((len1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			buffer_read;
	int			idx;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((idx = find_new_line(rem)) == -1)
	{
		buffer_read = read_file(buffer, fd);
		if (buffer_read <= 0)
		{
			if (rem || *rem)
			{
				line = rem;
				free_ptr(&rem);
			}
			return (line);
		}
		if (!(rem = ft_strjoin(rem, buffer)))
			return (NULL);
	}
	line = ft_substr(rem, 0, idx + 1);
	rem = ft_substr(rem, idx + 1, ft_strlen(rem) - ft_strlen(line));
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("test.txt", O_RDONLY);
// 	//fd2 = open("test2.txt", O_RDONLY);
// 	//fd3 = open("test3.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		//line = get_next_line(fd2);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		// line = get_next_line(fd3);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
