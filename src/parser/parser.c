/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:25:10 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/08 10:49:58 by tuchikaw         ###   ########.fr       */
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
	char	**colors;

	colors = ft_split(line + 2, ',');
	for (int i = 0; i < 3; i++)
	{
		if (colors[i] == NULL)
		{
			free(colors[i]);
			continue ;
		}
		if (!is_number(colors[i]))
		{
			printf("Error: Invalid color value %s set to -1\n", colors[i]);
			color[i] = -1;
			free(colors[i]);
			continue ;
		}
		color[i] = atoi(colors[i]);
		free(colors[i]);
	}
	free(colors);
}

int	parse_texture(char *line, char **texture)
{
	int	i;

	if (*texture)
	{
		printf("Error: Texture path is set multiple times\n");
		return (1);
	}
	i = 3;
	while (line[i] == ' ')
		i++;
	*texture = strdup(line + i);
	return (0);
}

int	parse_map_line(char *line, char ***map, int *map_lines)
{
	if (ft_strlen(line) == 0)
		return (1);
	(*map)[*map_lines] = strdup(line);
	(*map_lines)++;
	return (0);
}

int	parse_config(t_cub3d *cub, const char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	int		map_end;
	int		map_lines;

	if (!check_cub_extension((char *)filename))
	{
		printf("Error: Invalid file extension\n");
		return (1);
	};
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	map_started = 0;
	map_end = 0;
	map_lines = 0;
	cub->map = malloc(sizeof(char *) * MAP_MAX_HEIGHT);
	line = get_next_line(fd);
	while (line)
	{
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (!map_started && ft_strncmp(line, "F ", 2) == 0)
			parse_color(line, cub->config.floor);
		else if (!map_started && ft_strncmp(line, "C ", 2) == 0)
			parse_color(line, cub->config.ceiling);
		else if (!map_started && ft_strncmp(line, "NO ", 3) == 0)
		{
			if (parse_texture(line, &cub->config.texture_files[0]) == 1)
			{
				free(line);
				close(fd);
				cub->map[map_lines] = NULL;
				return (1);
			}
		}
		else if (!map_started && ft_strncmp(line, "SO ", 3) == 0)
		{
			if (parse_texture(line, &cub->config.texture_files[1]) == 1)
			{
				free(line);
				close(fd);
				cub->map[map_lines] = NULL;
				return (1);
			}
		}
		else if (!map_started && ft_strncmp(line, "WE ", 3) == 0)
		{
			if (parse_texture(line, &cub->config.texture_files[2]) == 1)
			{
				free(line);
				close(fd);
				cub->map[map_lines] = NULL;
				return (1);
			}
		}
		else if (!map_started && ft_strncmp(line, "EA ", 3) == 0)
		{
			if (parse_texture(line, &cub->config.texture_files[3]) == 1)
			{
				free(line);
				close(fd);
				cub->map[map_lines] = NULL;
				return (1);
			}
		}
		else if (!map_end && (map_started || line[0] == '1' || line[0] == '0'))
		{
			map_started = 1;
			if (parse_map_line(line, &cub->map, &map_lines) == 1)
				map_end = 1;
		}
		else if (map_end && ft_strlen(line) > 0)
		{
			printf("Error: Invalid line after map\n");
			free(line);
			close(fd);
			cub->map[map_lines] = NULL;
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	cub->map[map_lines] = NULL;
	return (0);
}
