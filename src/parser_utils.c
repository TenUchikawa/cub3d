/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:56:14 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 10:31:32 by tuchikaw         ###   ########.fr       */
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

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			break ;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
