/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:26 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 15:03:52 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
	{
		printf("Error: MLX initialization failed\n");
		return (1);
	}
	cub3d->window = mlx_new_window(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (!cub3d->window)
	{
		printf("Error: Window creation failed\n");
		return (1);
	}
	return (0);
}
