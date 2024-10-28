/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:20:39 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/10/29 02:33:26 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	// void *mlx = mlx_init();
	// mlx_new_window(mlx, 800, 600, "Hello World");
	// mlx_loop(mlx);
	// return (0);

	parse_file("map/map.cub");
}