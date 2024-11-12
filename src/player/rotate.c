/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:17 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/12 12:04:53 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_cub3d *cub3d, int direction)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = ROT_SPEED;
	if (direction != 1)
		rot_speed = -ROT_SPEED;
	old_dir_x = cub3d->player.dir_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(rot_speed)
		- cub3d->player.dir_y * sin(rot_speed);
	cub3d->player.dir_y = old_dir_x * sin(rot_speed) + cub3d->player.dir_y
		* cos(rot_speed);
	old_plane_x = cub3d->player.plane_x;
	cub3d->player.plane_x = cub3d->player.plane_x * cos(rot_speed)
		- cub3d->player.plane_y * sin(rot_speed);
	cub3d->player.plane_y = old_plane_x * sin(rot_speed) + cub3d->player.plane_y
		* cos(rot_speed);
}

void	init_dda_x(t_cub3d *cub3d, t_dda *dda, double ray_dir_x)
{
	dda->delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (cub3d->player.x - (int)cub3d->player.x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = ((int)cub3d->player.x + 1.0 - cub3d->player.x)
			* dda->delta_dist_x;
	}
}

void	init_dda_y(t_cub3d *cub3d, t_dda *dda, double ray_dir_y)
{
	dda->delta_dist_y = fabs(1 / ray_dir_y);
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (cub3d->player.y - (int)cub3d->player.y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = ((int)cub3d->player.y + 1.0 - cub3d->player.y)
			* dda->delta_dist_y;
	}
}
