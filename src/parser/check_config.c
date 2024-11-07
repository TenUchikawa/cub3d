/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:36:31 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/08 07:44:08 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_xpm_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (filename[len - 4] == '.' && filename[len - 3] == 'x' && filename[len
		- 2] == 'p' && filename[len - 1] == 'm');
}
int	check_texture_paths(char *textures[4])
{
	char	*texture;
	int		fd;

	for (int i = 0; i < 4; i++)
	{
		texture = textures[i];
		if (!texture)
		{
			printf("Error: Texture path is not set\n");
			return (1);
		}
		if (!check_xpm_extension(texture))
		{
			printf("Error: Texture %s does not have .xpm extension\n", texture);
			return (1);
		}
		fd = open(texture, O_RDONLY);
		if (fd == -1)
		{
			printf("Error: Texture file not found %s\n", texture);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	check_colors(int color[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Error: Invalid color value %d\n", color[i]);
			return (1);
		}
	}
	return (0);
}

int	set_player_location(t_cub3d *cub, int i, int j)
{
	cub->player.x = j + 0.5;
	cub->player.y = i + 0.5;
	cub->player.dir_x = (cub->map[i][j] == 'E'
			|| cub->map[i][j] == 'W') ? 0 : 1;
	cub->player.dir_y = (cub->map[i][j] == 'S'
			|| cub->map[i][j] == 'N') ? 0 : 1;
	cub->player.plane_x = (cub->map[i][j] == 'E'
			|| cub->map[i][j] == 'W') ? 0.66 : 0;
	cub->player.plane_y = (cub->map[i][j] == 'S'
			|| cub->map[i][j] == 'N') ? 0.66 : 0;
}

int	check_player_start_location(t_cub3d *cub)
{
	int	player_count;

	player_count = 0;
	for (int i = 0; cub->map[i]; i++)
	{
		for (int j = 0; cub->map[i][j]; j++)
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				player_count++;
				set_player_location(cub, i, j);
			}
		}
	}
	if (player_count != 1)
	{
		printf("Error: Player start location is not set or set multiple times\n");
		return (1);
	}
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}
int	is_wall(char c)
{
	return (c == '1');
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

int	check_map_borders(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || !map[i + 1]) && !(map[i][j] == '1'))
				return (printf("Error: Map is not closed at top/bottom\n"), 1);
			if ((j == 0 || !map[i][j + 1]) && !(map[i][j] == '1'))
				return (printf("Error: Map is not closed at left/right\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}
int	check_config(t_cub3d *cub)
{
	if (check_texture_paths(cub->config.textures) == 1)
		return (1);
	if (check_colors(cub->config.floor) == 1)
		return (1);
	if (check_colors(cub->config.ceiling) == 1)
		return (1);
	if (check_player_start_location(cub) == 1)
		return (1);
	if (check_map_chars(cub->map) == 1)
		return (1);
	if (check_map_borders(cub->map) == 1)
		return (1);
	return (0);
}

