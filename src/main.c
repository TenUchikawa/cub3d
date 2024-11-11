/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 13:13:43 by tuchikaw         ###   ########.fr       */
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

int	load_textures(t_cub3d *cub3d)
{
	char		**tfs;
	t_texture	*ts;
	const char	*texture_paths[4];
	int			i;

	ts = cub3d->config.textures;
	tfs = cub3d->config.texture_files;
	texture_paths[0] = tfs[0];
	texture_paths[1] = tfs[1];
	texture_paths[2] = tfs[2];
	texture_paths[3] = tfs[3];
	i = 0;
	while (i < 4)
	{
		ts[i].img = mlx_xpm_file_to_image(cub3d->mlx, (char *)texture_paths[i],
				&ts[i].width, &ts[i].height);
		if (!ts[i].img)
			return (1);
		ts[i].data = mlx_get_data_addr(ts[i].img, &ts[i].bpp, &ts[i].size_line,
				&ts[i].endian);
		i++;
	}
	return (0);
}

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

// void	draw_wall_column(t_cub3d *cub3d, int x, int start, int end,
// 		int tex_index, double wall_x)
// {
// 	int		y;
// 	int		tex_x;
// 	int		tex_y;
// 	double	step;
// 	double	tex_pos;
// 	char	*pixel;
// 	char	*texture_data;
// 	int		color;
// 	int		line_height;
// 	char	*img_pixel;

// 	texture_data = cub3d->config.textures[tex_index].data;
// 	line_height = end - start;
// 	// テクスチャのX座標を計算
// 	tex_x = (int)(wall_x * cub3d->config.textures[tex_index].width);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= cub3d->config.textures[tex_index].width)
// 		tex_x = cub3d->config.textures[tex_index].width - 1;
// 	step = 1.0 * cub3d->config.textures[tex_index].height / line_height;
// 	tex_pos = (start - WINDOW_HEIGHT / 2 + line_height / 2) * step;
// 	for (y = start; y < end; y++)
// 	{
// 		tex_y = (int)tex_pos & (cub3d->config.textures[tex_index].height - 1);
// 		tex_pos += step;
// 		pixel = texture_data + (tex_y
// 				* cub3d->config.textures[tex_index].size_line + tex_x
// 				* (cub3d->config.textures[tex_index].bpp / 8));
// 		color = *(unsigned int *)pixel;
// 		img_pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp
// 					/ 8));
// 		*(unsigned int *)img_pixel = color;
// 	}
// }

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

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*img_pixel;

	img_pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp / 8));
	*(unsigned int *)img_pixel = color;
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

void	draw_column(t_cub3d *cub3d, int x, t_ray *ray)
{
	t_wall_column	col;

	col.start = ray->draw_start;
	col.end = ray->draw_end;
	col.tex_index = ray->tex_index;
	col.wall_x = ray->wall_x;
	draw_wall_column(cub3d, x, &col);
}

int	draw_scene(void *param)
{
	t_cub3d	*cub3d;
	t_ray	ray;
	int		x;

	cub3d = (t_cub3d *)param;
	draw_floor_and_ceiling(cub3d);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_ray(cub3d, &ray, x);
		draw_column(cub3d, x, &ray);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->img, 0, 0);
	return (0);
}

void	setup_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->window, 2, 1L << 0, handle_keypress, cub3d);
	mlx_loop_hook(cub3d->mlx, draw_scene, cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	init_config((&cub3d));
	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	if (parse_config(&cub3d, argv[1]) == 1)
	{
		printf("Error Failed to parse config\n");
		exit(1);
	}
	if (check_config(&cub3d) == 1)
		exit(1);
	if (init_window(&cub3d) == 1)
		exit(1);
	if (init_image(&cub3d) == 1)
		exit(1);
	setup_hooks(&cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
