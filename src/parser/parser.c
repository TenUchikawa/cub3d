/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:20 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 15:03:39 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_config(t_cub3d *cub, const char *filename)
{
	int	fd;

	if (!check_cub_extension((char *)filename))
		return (printf("Error: Invalid file extension\n"), 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	cub->map = malloc(sizeof(char *) * MAP_MAX_HEIGHT);
	if (!cub->map)
		return (perror("Memory allocation error"), close(fd), 1);
	if (parse_settings_and_map(cub, fd))
		return (close(fd), 1);
	close(fd);
	cub->map[cub->map_height] = NULL;
	return (0);
}

int	parse_settings(t_cub3d *cub, char *line)
{
	line = skip_whitespace(line);
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

int	parse_settings_and_map(t_cub3d *cub, int fd)
{
	char	*line;
	int		map_started;
	int		parse_result;
	int		map_end;

	map_started = 0;
	map_end = 0;
	line = get_next_line(fd);
	while (line)
	{
		replace_end_nl_to_eol(line);
		if (!map_started)
			parse_result = parse_settings(cub, line);
		if (parse_result == 1)
			return (free(line), 1);
		else if (parse_result == 2)
			map_started = 1;
		if (map_started && parse_map_line(cub, line) == 1)
			map_end = 1;
		else if (map_end && *skip_whitespace(line))
			return (printf("Error: Invalid line after map\n"), free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
