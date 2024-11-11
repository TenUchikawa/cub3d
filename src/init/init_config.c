/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:25 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 14:32:45 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_config(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		cub->config.floor[i] = -1;
		cub->config.ceiling[i] = -1;
	}
	i = -1;
	while (++i < 4)
	{
		cub->config.texture_files[i] = NULL;
	}
	cub->map_height = 0;
	cub->map_width = 0;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	return (0);
}

int	check_cub_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(&filename[len - 4], ".cub", 4) == 0);
}

int	check_xpm_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(&filename[len - 4], ".xpm", 4) == 0);
}
