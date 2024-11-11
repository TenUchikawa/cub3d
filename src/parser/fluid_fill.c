/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:09:32 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 10:02:29 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

// 方向ベクトル (上下左右)

int	is_out_of_bounds(t_cub3d *cub, int x, int y)
{
	return (y < 0 || y >= cub->map_height || x < 0 || x >= cub->map_width);
}

/**
 * @brief マップを再帰的に探索して、壁で囲まれているかチェックします。
 *
 * @param cub cub3dの設定
 * @param x チェック開始のx座標
 * @param y チェック開始のy座標
 * @return int 壁で囲まれていれば1、囲まれていなければ0
 */
int	flood_fill(t_cub3d *cub, int x, int y, int directions[4][2])
{
	int	new_x;
	int	new_y;
	int	i;

	if (is_out_of_bounds(cub, x, y))
		return (0);
	if (cub->map[y][x] == '1' || cub->map[y][x] == 'V')
		return (1);
	if (cub->map[y][x] == ' ')
		return (0);
	cub->map[y][x] = 'V';
	i = -1;
	while (++i < 4)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];
		if (!flood_fill(cub, new_x, new_y, directions))
		{
			return (0);
		}
	}
	return (1);
}

/**
 * @brief マップが壁で正しく囲まれているかを検証します。
 *
 * @param cub cub3dの設定
 * @return int 正しく囲まれていれば0、囲まれていなければ1
 * 	directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
 */
int	validate_map(t_cub3d *cub)
{
	int	directions[4][2];

	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
	if (!flood_fill(cub, cub->player.x - 0.5, cub->player.y - 0.5, directions))
	{
		printf("Error: The map is not properly enclosed by walls.\n");
		return (1);
	}
	return (0);
}
