/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:08 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/12 12:06:43 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_char[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_char[fd] = get_to_next_newline(fd, static_char[fd]);
	if (!static_char[fd])
		return (NULL);
	line = get_to_nr(static_char[fd]);
	static_char[fd] = get_new_line(static_char[fd]);
	if (!line || line[0] == '\0')
		return (free(static_char[fd]), NULL);
	if (!static_char[fd] && (!line || line[0] == '\0'))
		return (NULL);
	return (line);
}

char	*get_new_line(char *static_char)
{
	char	*newline_address;
	int		new_char_len;
	char	*new_char;

	newline_address = ft_strchr(static_char, '\n');
	if (!newline_address)
	{
		free(static_char);
		return (NULL);
	}
	new_char_len = ft_strlen(newline_address + 1);
	new_char = (char *)malloc(sizeof(char) * (new_char_len + 1));
	if (!new_char)
	{
		free(static_char);
		return (NULL);
	}
	ft_memcpy(new_char, newline_address + 1, (new_char_len));
	free(static_char);
	new_char[new_char_len] = '\0';
	return (new_char);
}

char	*get_to_next_newline(int fd, char *static_char)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(static_char, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		static_char = ft_strjoin(static_char, buffer);
		if (!static_char)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (static_char);
}

char	*get_to_nr(char *static_char)
{
	char	*newline_address;
	char	*line;
	int		strlen;

	if (!static_char || static_char[0] == '\0')
		return (NULL);
	newline_address = ft_strchr(static_char, '\n');
	if (!newline_address)
	{
		line = (char *)malloc(sizeof(int) * (ft_strlen(static_char) + 1));
		if (!line)
			return (NULL);
		ft_memcpy(line, static_char, ft_strlen(static_char));
		line[ft_strlen(static_char)] = '\0';
		return (line);
	}
	strlen = newline_address - static_char + 1;
	line = (char *)malloc(sizeof(int) * (strlen + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, static_char, strlen);
	line[strlen] = '\0';
	return (line);
}
