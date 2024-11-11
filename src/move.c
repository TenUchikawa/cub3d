/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:31:22 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 10:45:15 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_cub3d *cub3d, int direction)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = MOVE_SPEED;
	if (direction != 1)
		move_step = -MOVE_SPEED;
	new_x = cub3d->player.x + cub3d->player.dir_x * move_step;
	new_y = cub3d->player.y + cub3d->player.dir_y * move_step;
	if (cub3d->map[(int)new_y][(int)cub3d->player.x] != '1')
		cub3d->player.y = new_y;
	if (cub3d->map[(int)cub3d->player.y][(int)new_x] != '1')
		cub3d->player.x = new_x;
}

void	strafe_player(t_cub3d *cub3d, int direction)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = MOVE_SPEED;
	if (direction != 1)
		move_step = -MOVE_SPEED;
	new_x = cub3d->player.x + cub3d->player.plane_x * move_step;
	new_y = cub3d->player.y + cub3d->player.plane_y * move_step;
	if (cub3d->map[(int)new_y][(int)cub3d->player.x] != '1')
		cub3d->player.y = new_y;
	if (cub3d->map[(int)cub3d->player.y][(int)new_x] != '1')
		cub3d->player.x = new_x;
}

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
