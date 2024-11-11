/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:31:58 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/10 14:43:04 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 'w' || keycode == 'W')
		move_player(cub3d, 1);
	else if (keycode == 's' || keycode == 'S')
		move_player(cub3d, -1);
	else if (keycode == 'a' || keycode == 'A')
		strafe_player(cub3d, -1);
	else if (keycode == 'd' || keycode == 'D')
		strafe_player(cub3d, 1);
	else if (keycode == 65361)
		rotate_player(cub3d, -1);
	else if (keycode == 65363)
		rotate_player(cub3d, 1);
	return (0);
}
