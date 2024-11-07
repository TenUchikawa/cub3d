/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:25:10 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/07 21:48:22 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	parse_color(char *line, int color[3])
{
	char **colors = ft_split(line + 2, ','); // ft_splitはカンマで分割する関数と仮定
	for (int i = 0; i < 3; i++)
	{
		color[i] = atoi(colors[i]);
		free(colors[i]);
	}
	free(colors);
}

void	parse_texture(char *line, char **texture)
{
	*texture = strdup(line + 3); // 3文字目以降がファイルパス
}

int	parse_map_line(char *line, char ***map, int *map_lines)
{
	(*map)[*map_lines] = strdup(line);
	(*map_lines)++;
	return (1);
}

int	parse_config(t_cub3d *cub, const char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	int		map_lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	map_started = 0;
	map_lines = 0;
	cub->map = malloc(sizeof(char *) * 100); // 仮の最大マップ行数
	while (get_next_line(fd, &line) > 0)
	{
		if (strncmp(line, "F ", 2) == 0)
			parse_color(line, cub->config.floor);
		else if (strncmp(line, "C ", 2) == 0)
			parse_color(line, cub->config.ceiling);
		else if (strncmp(line, "NO ", 3) == 0)
			parse_texture(line, &cub->config.textures[0]);
		else if (strncmp(line, "SO ", 3) == 0)
			parse_texture(line, &cub->config.textures[1]);
		else if (strncmp(line, "WE ", 3) == 0)
			parse_texture(line, &cub->config.textures[2]);
		else if (strncmp(line, "EA ", 3) == 0)
			parse_texture(line, &cub->config.textures[3]);
		else if (map_started || line[0] == '1')
		{
			map_started = 1;
			parse_map_line(line, &cub->map, &map_lines);
		}
		free(line);
	}
	close(fd);
	cub->map[map_lines] = NULL; // 最後にNULLで終わるようにする
	return (0);
}
