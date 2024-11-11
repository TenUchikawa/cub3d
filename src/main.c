/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 09:51:56 by tuchikaw         ###   ########.fr       */
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
	const char	*texture_paths[4] = {cub3d->config.texture_files[0],
			cub3d->config.texture_files[1], cub3d->config.texture_files[2],
			cub3d->config.texture_files[3]};

	for (int i = 0; i < 4; i++)
	{
		cub3d->config.textures[i].img = mlx_xpm_file_to_image(cub3d->mlx,
				(char *)texture_paths[i], &cub3d->config.textures[i].width,
				&cub3d->config.textures[i].height);
		if (!cub3d->config.textures[i].img)
			return (1); // エラーハンドリング
		cub3d->config.textures[i].data = mlx_get_data_addr(cub3d->config.textures[i].img,
				&cub3d->config.textures[i].bpp,
				&cub3d->config.textures[i].size_line,
				&cub3d->config.textures[i].endian);
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



void	draw_wall_column(t_cub3d *cub3d, int x, int start, int end,
		int tex_index, double wall_x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	char	*pixel;
	char	*texture_data;
	int		color;
	int		line_height;
	char	*img_pixel;

	texture_data = cub3d->config.textures[tex_index].data;
	line_height = end - start;
	// テクスチャのX座標を計算
	tex_x = (int)(wall_x * cub3d->config.textures[tex_index].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= cub3d->config.textures[tex_index].width)
		tex_x = cub3d->config.textures[tex_index].width - 1;
	step = 1.0 * cub3d->config.textures[tex_index].height / line_height;
	tex_pos = (start - WINDOW_HEIGHT / 2 + line_height / 2) * step;
	for (y = start; y < end; y++)
	{
		tex_y = (int)tex_pos & (cub3d->config.textures[tex_index].height - 1);
		tex_pos += step;
		pixel = texture_data + (tex_y
				* cub3d->config.textures[tex_index].size_line + tex_x
				* (cub3d->config.textures[tex_index].bpp / 8));
		color = *(unsigned int *)pixel;
		img_pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp
					/ 8));
		*(unsigned int *)img_pixel = color;
	}
}
double	cast_ray(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y,
		int *tex_index, double *wall_x)
{
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;

	map_x = (int)cub3d->player.x;
	map_y = (int)cub3d->player.y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	double side_dist_x, side_dist_y;
	int step_x, step_y, hit = 0, side;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (cub3d->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - cub3d->player.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (cub3d->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - cub3d->player.y) * delta_dist_y;
	}
	// DDAアルゴリズムでRayを進め、壁との衝突を検出
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (cub3d->map[map_y][map_x] == '1')
			hit = 1;
	}
	// 壁までの距離を計算
	if (side == 0)
	{
		perp_wall_dist = (side_dist_x - delta_dist_x);
		*wall_x = cub3d->player.y + perp_wall_dist * ray_dir_y;
		*tex_index = (ray_dir_x > 0) ? 2 : 3; // 西か東
	}
	else
	{
		perp_wall_dist = (side_dist_y - delta_dist_y);
		*wall_x = cub3d->player.x + perp_wall_dist * ray_dir_x;
		*tex_index = (ray_dir_y > 0) ? 0 : 1; // 北か南
	}
	*wall_x -= floor(*wall_x);
	return (perp_wall_dist);
}
int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
void	draw_floor_and_ceiling(t_cub3d *cub3d)
{
	int		ceiling_color;
	int		floor_color;
	char	*pixel;

	ceiling_color = create_color(cub3d->config.ceiling[0],
			cub3d->config.ceiling[1], cub3d->config.ceiling[2]);
	floor_color = create_color(cub3d->config.floor[0], cub3d->config.floor[1],
			cub3d->config.floor[2]);
	int x, y;
	// 天井の描画
	for (y = 0; y < WINDOW_HEIGHT / 2; y++)
	{
		for (x = 0; x < WINDOW_WIDTH; x++)
		{
			pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp
						/ 8));
			*(unsigned int *)pixel = ceiling_color;
		}
	}
	// 床の描画
	for (y = WINDOW_HEIGHT / 2; y < WINDOW_HEIGHT; y++)
	{
		for (x = 0; x < WINDOW_WIDTH; x++)
		{
			pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp
						/ 8));
			*(unsigned int *)pixel = floor_color;
		}
	}
}

int	draw_scene(void *param)
{
	t_cub3d	*cub3d;
	int		x;

	cub3d = (t_cub3d *)param;
	double camera_x, ray_dir_x, ray_dir_y;
	double perp_wall_dist, wall_x;
	int line_height, draw_start, draw_end, tex_index;
	// 天井と床の描画
	draw_floor_and_ceiling(cub3d);
	// 壁の描画
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		ray_dir_x = cub3d->player.dir_x + cub3d->player.plane_x * camera_x;
		ray_dir_y = cub3d->player.dir_y + cub3d->player.plane_y * camera_x;
		perp_wall_dist = cast_ray(cub3d, ray_dir_x, ray_dir_y, &tex_index,
				&wall_x);
		line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		draw_wall_column(cub3d, x, draw_start, draw_end, tex_index, wall_x);
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
	t_cub3d cub3d;

	init_config((&cub3d));

	if (argc != 2)
	{
		// printf("Usage: %s <map_file>\n", argv[0]);
		// return (1);
		argv[1] = "maps/good/test_whitespace.cub";
	}

	if (parse_config(&cub3d, argv[1]) == 1)
	{
		printf("Error Failed to parse config\n");
		exit(1);
	}

	// マップの表示
	// for (int i = 0; cub3d.map[i]; i++)
	// {
	// 	printf("%s\n", cub3d.map[i]);
	// }

	if (check_config(&cub3d) == 1)
	{
		exit(1);
	}

	// configの表示
	// printf("Floor color: %d, %d, %d\n", cub3d.config.floor[0],
	// 	cub3d.config.floor[1], cub3d.config.floor[2]);
	// printf("Ceiling color: %d, %d, %d\n", cub3d.config.ceiling[0],
	// 	cub3d.config.ceiling[1], cub3d.config.ceiling[2]);
	// printf("NO texture: %s\n", cub3d.config.textures[0]);
	// printf("SO texture: %s\n", cub3d.config.textures[1]);
	// printf("WE texture: %s\n", cub3d.config.textures[2]);
	// printf("EA texture: %s\n", cub3d.config.textures[3]);

	// if (init_window(&cub3d) == 1)
	// 	return (1);
	// if (init_image(&cub3d) == 1)
	// 	return (1);
	// setup_hooks(&cub3d);
	// mlx_loop(cub3d.mlx);

	return (0);
}