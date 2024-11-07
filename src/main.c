/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/08 07:53:54 by tuchikaw         ###   ########.fr       */
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
int	draw_scene(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	mlx_clear_window(cub3d->mlx, cub3d->window);
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