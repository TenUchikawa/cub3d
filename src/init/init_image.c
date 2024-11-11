/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:25 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 15:03:49 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_image(t_cub3d *cub3d)
{
	if (load_textures(cub3d) == 1)
		return (1);
	cub3d->img = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->img)
	{
		printf("Error: Image creation failed\n");
		return (1);
	}
	cub3d->img_data = mlx_get_data_addr(cub3d->img, &cub3d->bpp,
			&cub3d->size_line, &cub3d->endian);
	return (0);
}

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*img_pixel;

	img_pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp / 8));
	*(unsigned int *)img_pixel = color;
}
