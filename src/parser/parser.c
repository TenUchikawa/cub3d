/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:25:10 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 09:45:10 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	parse_color(char *line, int color[3])
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
	return (0);
}

int	parse_texture(char *line, char **texture)
{
	int	i;

	if (*texture)
	{
		printf("Error: Texture path is set multiple times\n");
		return (1);
	}
	
	*texture = ft_strtrim(line+3," \t\n");
	return (0);
}

int	parse_map_line(t_cub3d *cub, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (cub->map_width < len)
		cub->map_width = len;
	if (len == 0)
		return (1);
	cub->map[cub->map_height] = strdup(line);
	cub->map_height++;
	// printf("%s\n", line);
	return (0);
}
char	*skip_whitespace(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

int	parse_settings(t_cub3d *cub, char *line)
{
	line = skip_whitespace(line);
	// printf("%s\n", line);
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line, cub->config.floor));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line, cub->config.ceiling));
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line, &cub->config.texture_files[0]));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line, &cub->config.texture_files[1]));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line, &cub->config.texture_files[2]));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line, &cub->config.texture_files[3]));
	return (2);
}
int	parse_config(t_cub3d *cub, const char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	int		map_end;
	int		parse_result;

	if (!check_cub_extension((char *)filename))
	{
		printf("Error: Invalid file extension\n");
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	map_started = 0;
	map_end = 0;
	cub->map = malloc(sizeof(char *) * MAP_MAX_HEIGHT);
	if (!cub->map)
		return (perror("Memory allocation error"), close(fd), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (!map_started)
			parse_result = parse_settings(cub, line);
		if (parse_result == 1)
		{
			free(line);
			close(fd);
			return (1);
		}
		else if (parse_result == 2)
			map_started = 1;
		if (!map_end && map_started)
		{
			if (parse_map_line(cub, line) == 1)
				map_end = 1;
		}
		else if (map_end && *skip_whitespace(line))
		{

			
			printf("Error: Invalid line after map\n");
			free(line);
			close(fd);
			cub->map[cub->map_height] = NULL;
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	cub->map[cub->map_height] = NULL;
	return (0);
}
