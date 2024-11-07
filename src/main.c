/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/08 08:19:28 by tuchikaw         ###   ########.fr       */
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

int	init_image(t_cub3d *cub3d)
{
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

void	draw_test_wall(t_cub3d *cub3d)
{
	int		y;
	char	*pixel;

	int x = WINDOW_WIDTH / 2; // 画面中央のx座標
	y = 0;
	while (y < WINDOW_HEIGHT) // 画面の高さ全体に渡る縦線を描画
	{
		pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp / 8));
		*(unsigned int *)pixel = 0xFFFFFF; // 白色のピクセルを設定
		y++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->img, 0, 0);
	// ウィンドウに画像を表示
}

void	draw_wall_column(t_cub3d *cub3d, int x, int start, int end, int color)
{
	int		y;
	char	*pixel;

	y = start;
	while (y < end)
	{
		pixel = cub3d->img_data + (y * cub3d->size_line + x * (cub3d->bpp / 8));
		*(unsigned int *)pixel = color; // 壁の色をセット
		y++;
	}
}

double	cast_ray(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y)
{
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;

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
			hit = 1; // 壁に衝突
	}
	return (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y
		- delta_dist_y);
}
int	draw_scene(void *param)
{
	t_cub3d	*cub3d;
	int		x;
	double	perp_wall_dist;
	int		color;

	cub3d = (t_cub3d *)param;
	x = 0;
	double camera_x, ray_dir_x, ray_dir_y;
	int line_height, draw_start, draw_end;
	// 画像バッファをクリア
	mlx_clear_window(cub3d->mlx, cub3d->window);
	while (x < WINDOW_WIDTH)
	{
		// カメラ面のX座標を計算
		camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		ray_dir_x = cub3d->player.dir_x + cub3d->player.plane_x * camera_x;
		ray_dir_y = cub3d->player.dir_y + cub3d->player.plane_y * camera_x;
		// 壁までの距離を取得
		perp_wall_dist = cast_ray(cub3d, ray_dir_x, ray_dir_y);
		// 距離に基づいて線の高さを計算
		line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		// 画面外に出ないようにクリッピング
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		// 壁の色（テスト用に白）
		color = 0xFFFFFF;
		// 壁を描画
		draw_wall_column(cub3d, x, draw_start, draw_end, color);
		x++;
	}
	// 描画した画像をウィンドウに表示
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->img, 0, 0);
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->window);
		exit(0);
	}
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

	init_config(&cub3d.config);

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}

	if (parse_config(&cub3d, argv[1]) == -1)
	{
		printf("Error\nFailed to parse config\n");
		return (1);
	}

	// マップの表示
	// for (int i = 0; cub3d.map[i]; i++)
	// {
	// 	printf("%s\n", cub3d.map[i]);
	// }

	if (check_config(&cub3d) == 1)
	{
		return (1);
	}

	// configの表示
	printf("Floor color: %d, %d, %d\n", cub3d.config.floor[0],
		cub3d.config.floor[1], cub3d.config.floor[2]);
	printf("Ceiling color: %d, %d, %d\n", cub3d.config.ceiling[0],
		cub3d.config.ceiling[1], cub3d.config.ceiling[2]);
	// printf("NO texture: %s\n", cub3d.config.textures[0]);
	// printf("SO texture: %s\n", cub3d.config.textures[1]);
	// printf("WE texture: %s\n", cub3d.config.textures[2]);
	// printf("EA texture: %s\n", cub3d.config.textures[3]);

	if (init_window(&cub3d) == 1)
		return (1);
	if (init_image(&cub3d) == 1)
		return (1);
	setup_hooks(&cub3d);
	mlx_loop(cub3d.mlx);
	// cub3d.mlx = mlx_init();
	// cub3d.window = mlx_new_window(cub3d.mlx, 640, 480, "cub3D");

	// メインループ
	// mlx_loop_hook(cub3d.mlx, render_frame, &cub3d);
	// mlx_hook(cub3d.window, 2, 1L << 0, handle_input, &cub3d);
	// mlx_loop(cub3d.mlx);

	return (0);
}