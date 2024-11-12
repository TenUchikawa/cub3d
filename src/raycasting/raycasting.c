/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:13 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/12 11:58:19 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cast_ray(t_cub3d *cub3d, t_ray *ray)
{
	int		map_x;
	int		map_y;
	t_dda	dda;

	map_x = (int)cub3d->player.x;
	map_y = (int)cub3d->player.y;
	init_dda(cub3d, &dda, ray->ray_dir_x, ray->ray_dir_y);
	perform_dda(cub3d, &dda, &map_x, &map_y);
	ray->tex_index = determine_texture(ray, &dda);
	return (calculate_wall_distance(cub3d, ray, &dda, &ray->wall_x));
}

void	calculate_ray(t_cub3d *cub3d, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = cub3d->player.dir_x + cub3d->player.plane_x
		* ray->camera_x;
	ray->ray_dir_y = cub3d->player.dir_y + cub3d->player.plane_y
		* ray->camera_x;
	ray->perp_wall_dist = cast_ray(cub3d, ray);
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

void	init_dda(t_cub3d *cub3d, t_dda *dda, double ray_dir_x, double ray_dir_y)
{
	init_dda_x(cub3d, dda, ray_dir_x);
	init_dda_y(cub3d, dda, ray_dir_y);
}

int	perform_dda(t_cub3d *cub3d, t_dda *dda, int *map_x, int *map_y)
{
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			*map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			*map_y += dda->step_y;
			dda->side = 1;
		}
		if (cub3d->map[*map_y][*map_x] == '1')
			return (1);
	}
}

int	determine_texture(t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (0);
		else
			return (1);
	}
}
