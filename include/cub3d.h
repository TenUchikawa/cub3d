/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:30:50 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/07 21:37:42 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42_libft/libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structures

typedef struct s_config
{
	int			floor[3];
	int			ceiling[3];
	char *textures[4]; // NO, SO, WE, EA
}				t_config;

typedef struct s_player
{
	double x, y;             // プレイヤーの位置
	double dir_x, dir_y;     // プレイヤーの向き
	double plane_x, plane_y; // カメラ平面
}				t_player;

typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_config	config;
	t_player	player;
	char		**map;
}				t_cub3d;

// parser
int				parse_config(t_cub3d *cub, const char *filename);