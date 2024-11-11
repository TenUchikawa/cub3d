/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:30:50 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 14:54:08 by tuchikaw         ###   ########.fr       */
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

# ifndef MOVE_SPEED
#  define MOVE_SPEED 0.1
# endif

# ifndef ROT_SPEED
#  define ROT_SPEED 0.05
# endif

// structures

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_config
{
	int			floor[3];
	int			ceiling[3];
	char *texture_files[4]; // NO, SO, WE, EA
	t_texture	textures[4];

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
	int			map_height;
	int			map_width;

	void *img;      // 画像データ用フィールド
	char *img_data; // ピクセルデータにアクセスするためのアドレス
	int bpp;        // 1ピクセルあたりのビット数
	int size_line;  // 1行分のデータサイズ
	int endian;     // エンディアン情報

}				t_cub3d;

typedef struct s_wall_column
{
	int			start;
	int			end;
	int			tex_index;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	char		*texture_data;
}				t_wall_column;
typedef struct s_dda
{
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_dda;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_index;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

// parser
int				parse_config(t_cub3d *cub, const char *filename);
int				check_config(t_cub3d *cub);
int				init_config(t_cub3d *cub);
int				is_number(char *str);
int				check_cub_extension(char *filename);
int				validate_map(t_cub3d *cub3d);

// key_handle
int				handle_keypress(int keycode, t_cub3d *cub3d);

// move
void			move_player(t_cub3d *cub3d, int direction);
void			strafe_player(t_cub3d *cub3d, int direction);
void			rotate_player(t_cub3d *cub3d, int direction);
char			*skip_whitespace(char *line);
void			init_dda(t_cub3d *cub3d, t_dda *dda, double ray_dir_x,
					double ray_dir_y);
void			init_dda_x(t_cub3d *cub3d, t_dda *dda, double ray_dir_x);
void			init_dda_y(t_cub3d *cub3d, t_dda *dda, double ray_dir_y);
int				perform_dda(t_cub3d *cub3d, t_dda *dda, int *map_x, int *map_y);
int				determine_texture(t_ray *ray, t_dda *dda);
double			calculate_wall_distance(t_cub3d *cub3d, t_ray *ray, t_dda *dda,
					double *wall_x);
double			cast_ray(t_cub3d *cub3d, t_ray *ray);

#endif