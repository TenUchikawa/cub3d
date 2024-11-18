/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/19 03:38:00 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	close_window(t_cub3d *cub)
{
	(void)cub;
	exit(0);
	return (0);
}

void	setup_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->window, 17, 0, close_window, &cub3d);
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
