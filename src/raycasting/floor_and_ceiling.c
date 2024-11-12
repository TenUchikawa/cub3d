/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:14 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/12 12:19:39 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_cub3d *cub3d)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = create_color(cub3d->config.ceiling[0],
			cub3d->config.ceiling[1], cub3d->config.ceiling[2]);
	floor_color = create_color(cub3d->config.floor[0], cub3d->config.floor[1],
			cub3d->config.floor[2]);
	draw_ceiling(cub3d, ceiling_color);
	draw_floor(cub3d, floor_color);
}

void	draw_ceiling(t_cub3d *cub3d, int ceiling_color)
{
	int		x;
	int		y;
	char	*pixel;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp
						/ 8));
			*(unsigned int *)pixel = ceiling_color;
			x++;
		}
		y++;
	}
}

void	draw_floor(t_cub3d *cub3d, int floor_color)
{
	int		x;
	int		y;
	char	*pixel;

	y = WINDOW_HEIGHT / 2;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp
						/ 8));
			*(unsigned int *)pixel = floor_color;
			x++;
		}
		y++;
	}
}

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
