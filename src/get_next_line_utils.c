/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:24:08 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/10/29 02:54:29 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

char	*get_to_nr(char *static_char)
{
	char	*newline_address;
	int		strlen;
	char	*line;

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
