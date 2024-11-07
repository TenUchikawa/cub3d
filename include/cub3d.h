/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:30:50 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/08 08:09:34 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "42_libft/libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef MAP_MAX_HEIGHT
#  define MAP_MAX_HEIGHT 256
# endif

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 640
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 480
# endif

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

	void *img;      // 画像データ用フィールド
	char *img_data; // ピクセルデータにアクセスするためのアドレス
	int bpp;        // 1ピクセルあたりのビット数
	int size_line;  // 1行分のデータサイズ
	int endian;     // エンディアン情報

}				t_cub3d;

// parser
int				parse_config(t_cub3d *cub, const char *filename);
int				check_config(t_cub3d *cub);
int				init_config(t_config *config);
int				is_number(char *str);
#endif