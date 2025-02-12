/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:03:05 by dheck             #+#    #+#             */
/*   Updated: 2024/05/03 09:42:54 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_create_line(char **remainder, char **line);
static char	*ft_read_file(int fd, char **remainder);

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
	{
		return (NULL);
	}
	line = NULL;
	remainder = ft_read_file(fd, &remainder);
	if (remainder == NULL)
		return (NULL);
	line = ft_create_line(&remainder, &line);
	if (line != NULL)
	{
		return (line);
	}
	return (free(remainder), NULL);
}

static char	*ft_create_line(char **remainder, char **line)
{
	int		newline;
	size_t	size;
	char	*tmp;

	newline = ft_gnl_strchr(*remainder, '\n');
	size = ft_strlen(*remainder);
	if (size == 0)
		return (NULL);
	if (size > 0 && newline >= 0)
	{
		*line = ft_substr(*remainder, 0, newline + 1);
		tmp = ft_substr(*remainder, newline + 1, size - newline);
		if (tmp == NULL)
			return (free(*line), NULL);
		free(*remainder);
		*remainder = tmp;
		return (*line);
	}
	else if (size > 0 && newline == -1)
	{
		*line = *remainder;
		*remainder = NULL;
		return (*line);
	}
	return (NULL);
}

static char	*ft_read_file(int fd, char **remainder)
{
	int		bytes_read;
	char	*tmp;
	char	*f_buffer;

	f_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (f_buffer == NULL)
		return (NULL);
	if (*remainder == NULL)
		*remainder = ft_strdup("\0");
	bytes_read = read(fd, f_buffer, BUFFER_SIZE);
	if (bytes_read <= 0 && ft_strlen(*remainder) == 0)
		return (free(*remainder), free(f_buffer), NULL);
	while (bytes_read > 0)
	{
		f_buffer[bytes_read] = '\0';
		tmp = ft_strjoin(*remainder, f_buffer);
		free(*remainder);
		if (tmp == NULL)
			return (free(f_buffer), NULL);
		*remainder = tmp;
		if (ft_gnl_strchr(*remainder, '\n') > -1)
			break ;
		bytes_read = read(fd, f_buffer, BUFFER_SIZE);
	}
	return (free(f_buffer), *remainder);
}

int	ft_gnl_strchr(const char *s, int c)
{
	const char	*p_s;

	p_s = s;
	if (!s)
		return (-1);
	while (*p_s != '\0')
	{
		if (*p_s == c)
			return (p_s - s);
		p_s++;
	}
	return (-1);
}
