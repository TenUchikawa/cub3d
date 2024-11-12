/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:15 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/12 12:01:57 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_cub3d *cub3d, int x, t_ray *ray)
{
	t_wall_column	col;

	col.start = ray->draw_start;
	col.end = ray->draw_end;
	col.tex_index = ray->tex_index;
	col.wall_x = ray->wall_x;
	draw_wall_column(cub3d, x, &col);
}

void	draw_wall_column(t_cub3d *cub3d, int x, t_wall_column *col)
{
	int			y;
	int			color;
	t_texture	*texture;

	texture = &cub3d->config.textures[col->tex_index];
	init_wall_column(cub3d, col);
	y = col->start;
	while (y < col->end)
	{
		col->tex_y = (int)col->tex_pos & (texture->height - 1);
		col->tex_pos += col->step;
		color = *(unsigned int *)(col->texture_data + col->tex_y
				* texture->size_line + col->tex_x * (texture->bpp / 8));
		draw_pixel(cub3d, x, y, color);
		y++;
	}
}

void	init_wall_column(t_cub3d *cub3d, t_wall_column *col)
{
	t_texture	*texture;

	texture = &cub3d->config.textures[col->tex_index];
	col->texture_data = texture->data;
	col->tex_x = (int)(col->wall_x * texture->width);
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= texture->width)
		col->tex_x = texture->width - 1;
	col->step = 1.0 * texture->height / (col->end - col->start);
	col->tex_pos = (col->start - WINDOW_HEIGHT / 2 + (col->end - col->start)
			/ 2) * col->step;
}

int	get_tex_x(t_texture *texture, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

double	calculate_wall_distance(t_cub3d *cub3d, t_ray *ray, t_dda *dda,
		double *wall_x)
{
	double	perp_wall_dist;

	if (dda->side == 0)
	{
		perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
		*wall_x = cub3d->player.y + perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
		*wall_x = cub3d->player.x + perp_wall_dist * ray->ray_dir_x;
	}
	*wall_x -= floor(*wall_x);
	return (perp_wall_dist);
}
