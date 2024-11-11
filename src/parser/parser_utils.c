/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:21 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/11 15:03:29 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *line, int color[3])
{
	char	**colors;
	int		i;

	colors = ft_split(line + 2, ',');
	i = -1;
	while (++i < 3)
	{
		if (colors[i] == NULL)
		{
			free(colors[i]);
			continue ;
		}
		if (!is_number(colors[i]))
		{
			printf("Error: Invalid color value %s set to -1\n", colors[i]);
			color[i] = -1;
			free(colors[i]);
			continue ;
		}
		color[i] = atoi(colors[i]);
		free(colors[i]);
	}
	free(colors);
	return (0);
}

int	parse_texture(char *line, char **texture)
{
	int	i;

	if (*texture)
	{
		printf("Error: Texture path is set multiple times\n");
		return (1);
	}
	*texture = ft_strtrim(line + 3, " \t\n");
	return (0);
}

int	parse_map_line(t_cub3d *cub, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (cub->map_width < len)
		cub->map_width = len;
	if (len == 0)
		return (1);
	cub->map[cub->map_height] = strdup(line);
	cub->map_height++;
	return (0);
}

char	*skip_whitespace(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

void	replace_end_nl_to_eol(char *line)
{
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
}
