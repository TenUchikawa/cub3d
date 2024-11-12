/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:18 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/12 12:04:28 by tuchikaw         ###   ########.fr       */
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
