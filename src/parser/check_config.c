/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:23 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 15:03:25 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_config(t_cub3d *cub)
{
	if (check_texture_paths(cub->config.texture_files) == 1)
		return (1);
	if (check_colors(cub->config.floor) == 1)
		return (1);
	if (check_colors(cub->config.ceiling) == 1)
		return (1);
	if (check_player_start_location(cub) == 1)
		return (1);
	if (check_map_chars(cub->map) == 1)
		return (1);
	if (validate_map(cub) == 1)
		return (1);
	return (0);
}

int	check_texture_paths(char *textures[4])
{
	char	*texture;
	int		fd;
	int		i;

	i = -1;
	while (++i < 4)
	{
		texture = textures[i];
		if (!texture)
			return (printf("Error: Texture path is not set\n"), 1);
		if (!check_xpm_extension(texture))
			return (printf("Error: Texture %s missing .xpm ext\n", texture), 1);
		fd = open(texture, O_RDONLY);
		if (fd == -1)
			return (printf("Error: Texture file not found %s\n", texture), 1);
		close(fd);
	}
	return (0);
}

int	check_colors(int color[3])
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Error: Invalid color value %d\n", color[i]);
			return (1);
		}
	}
	return (0);
}

int	check_player_start_location(t_cub3d *cub)
{
	int	player_count;
	int	y;
	int	x;

	player_count = 0;
	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
				|| cub->map[y][x] == 'W' || cub->map[y][x] == 'E')
			{
				player_count++;
				set_player_location(cub, x, y);
			}
		}
	}
	if (player_count != 1)
	{
		printf("Error: Player start location missing or set multiple times\n");
		return (1);
	}
	return (0);
}

int	check_map_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
			{
				printf("Error: Invalid character '%c' in map\n", map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
