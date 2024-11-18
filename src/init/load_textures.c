/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:27 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/19 03:44:29 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_cub3d *cub3d)
{
	char		**tfs;
	t_texture	*ts;
	const char	*texture_paths[4];
	int			i;

	ts = cub3d->config.textures;
	tfs = cub3d->config.texture_files;
	texture_paths[0] = tfs[0];
	texture_paths[1] = tfs[1];
	texture_paths[2] = tfs[2];
	texture_paths[3] = tfs[3];
	i = 0;
	while (i < 4)
	{
		ts[i].img = mlx_xpm_file_to_image(cub3d->mlx, (char *)texture_paths[i],
				&ts[i].width, &ts[i].height);
		if (!ts[i].img)
			return (1);
		ts[i].data = mlx_get_data_addr(ts[i].img, &ts[i].bpp, &ts[i].size_line,
				&ts[i].endian);
		i++;
	}
	return (0);
}
