/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:36:12 by slasfar           #+#    #+#             */
/*   Updated: 2024/11/20 22:01:33 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readfile(char *remaining, int fd)
{
	char	*buffer;
	ssize_t	readsize;

	readsize = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (!(ft_strchr(buffer, '\n')) && readsize > 0)
	{
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize == -1)
			return (free(buffer), NULL);
		buffer[readsize] = '\0';
		remaining = ft_strjoin(remaining, buffer);
	}
	free(buffer);
	return (remaining);
}

char	*extract_line(char *remaining)
{
	char	*line;
	size_t	i;

	if (remaining[0] == '\0')
		return (NULL);
	i = get_index(remaining);
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remaining[i] && remaining[i] != '\n')
	{
		line[i] = remaining[i];
		i++;
	}
	if (remaining[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_remaining(char *remaining)
{
	char	*new_remaining;
	size_t	i;
	size_t	j;

	i = get_index(remaining);
	if (remaining[i] == '\0')
	{
		free(remaining);
		return (NULL);
	}
	new_remaining = (char *)malloc((ft_strlen(remaining) - i) * sizeof(char));
	if (!new_remaining)
		return (NULL);
	i++;
	j = 0;
	while (remaining[i])
		new_remaining[j++] = remaining[i++];
	new_remaining[j] = '\0';
	return (free(remaining), new_remaining);
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
	line = extract_line(remaining);
	remaining = update_remaining(remaining);
	return (line);
}
