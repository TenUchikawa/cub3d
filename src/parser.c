/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:25:10 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/10/29 02:56:15 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	parse_texture(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		printf("North texture: %s\n", line + 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		printf("South texture: %s\n", line + 3);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		printf("West texture: %s\n", line + 3);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		printf("East texture: %s\n", line + 3);
	}
	else if (line[0] == 'F')
	{
		printf("Floor color: %s\n", line + 2);
	}
	else if (line[0] == 'C')
	{
		printf("Ceiling color: %s\n", line + 2);
	}
	else
	{
		printf("Unknown element: %s\n", line);
	}
}

void	parse_file(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		// 1行ずつ処理する
		printf("Unknown element: %s\n", line);
		// parse_texture(line);
		free(line);
	}
	close(fd);
}