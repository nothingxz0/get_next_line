/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:05:30 by slasfar           #+#    #+#             */
/*   Updated: 2024/11/14 11:00:23 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 42
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	free_ptr(char **ptr);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		get_idx(char *str);

#endif
