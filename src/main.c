/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/07 21:48:28 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d cub3d;

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

	// cub3d.mlx = mlx_init();
	// cub3d.window = mlx_new_window(cub3d.mlx, 640, 480, "cub3D");

	// メインループ
	// mlx_loop_hook(cub3d.mlx, render_frame, &cub3d);
	// mlx_hook(cub3d.window, 2, 1L << 0, handle_input, &cub3d);
	// mlx_loop(cub3d.mlx);

	return (0);
}