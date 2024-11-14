/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 08:59:05 by slasfar           #+#    #+#             */
/*   Updated: 2024/11/14 11:05:27 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readfile(char *remaining, int fd)
{
	char	*buffer;
	int		read_size;
	
	read_size = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return (NULL);
	while(!ft_strchr(buffer, '\n') && read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			free_ptr(&buffer);
		buffer[read_size] = '\0';
		remaining = ft_strjoin(remaining, buffer);
	}
	free_ptr(&buffer);
	return (remaining);
}

char	*split_lines(char *str)
{
	char	*new_line;
	int		index;

	index = get_idx(str);
	new_line = (char *)malloc((index + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (str[index] && str[index] != '\n')
	{
			new_line[index] = str[index];
			index++;
	}
	if (str[index] == '\n')
		new_line[index++] = '\n';
	new_line[index] = '\0';
	return (new_line);
}

char	*trimline(char	*remaining)
{
	char	*new_remaining;
	int		i;
	int		j;

	i = get_idx(remaining);
	if (!(*remaining))
	{
		free_ptr(&remaining);
		return (NULL);
	}
	j = 0;
	new_remaining = (char *)malloc(sizeof(char) * (ft_strlen(remaining) - i));
	if (!new_remaining)
		return (NULL);
	i++;
	while (remaining[i])
		new_remaining[j++] = remaining[i++];
	new_remaining[j] = '\0';
	return (new_remaining);
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	remaining = readfile(remaining, fd);
	if (!remaining)
		return (NULL);
	line = split_lines(remaining);
	remaining = trimline(remaining);
	return (line);
}
