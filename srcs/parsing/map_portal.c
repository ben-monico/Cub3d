/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_portal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:44:01 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/17 14:38:14 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	easter_egg(t_cub *data)
{
	data->img.wall[5].ptr = mlx_xpm_file_to_image(data->mlx, \
	"img/easter.xpm", &data->img.wall[5].width, &data->img.wall[5].height);
	if (!data->img.wall[5].ptr)
		exit_free(data, 1, "Fail loading images");
	data->img.wall[5].addr = mlx_get_data_addr(data->img.wall[5].ptr, \
	&data->img.wall[5].bpp, &data->img.wall[5].size_line, \
	&data->img.wall[5].endian);
}

int	checker_zero(char **map, int y, int x)
{
	if (!map[y + 1] || (y - 1) < 0 || (x - 1) < 0 \
	|| !map[y - 1][x] || !map[y][x - 1] || !map[y + 1][x] || !map[y][x + 1] \
	|| !map[y + 1][x + 1] || !map[y - 1][x - 1] || !map[y + 1][x - 1] \
	|| !map[y - 1][x + 1])
		return (0);
	if (map[y - 1][x] == ' ' || map[y][x - 1] == ' ' || map[y + 1][x] == ' ' \
	|| map[y][x + 1] == ' ' || map[y + 1][x + 1] == ' ' \
	|| map[y - 1][x - 1] == ' ' || map[y + 1][x - 1] == ' ' \
	|| map[y - 1][x + 1] == ' ')
		return (0);
	if (map[y - 1][x] == '\n' || map[y][x - 1] == '\n' || map[y + 1][x] == '\n' \
	|| map[y][x + 1] == '\n' || map[y + 1][x + 1] == '\n' \
	|| map[y - 1][x - 1] == '\n' || map[y + 1][x - 1] == '\n' \
	|| map[y - 1][x + 1] == '\n')
		return (0);
	return (1);
}

void	check_portal(char **map, int x, int y)
{
	if (map[y][x - 1] == '0' && map[y][x + 1] == '0' &&
		(map[y + 1][x] == '0' || map[y - 1][x] == '0'))
	{
		printf("Line: %d Column: %d => '%c'\n", y, x, map[y][x]);
		exit_free(cube(), 1, "Invalid Use of Portal");
	}
	if (map[y + 1][x] == '0' && map[y - 1][x] == '0' &&
		(map[y][x + 1] == '0' || map[y][x - 1] == '0'))
	{
		printf("Line: %d Column: %d => '%c'\n", y, x, map[y][x]);
		exit_free(cube(), 1, "Invalid Use of Portal");
	}
	if (((map[y][x - 1] == '1' || map[y][x - 1] == '5') \
		&& (map[y][x + 1] == '0' || map[y][x + 1] == '2')) \
		|| ((map[y][x - 1] == '0' || map[y][x - 1] == '2') \
		&& (map[y][x + 1] == '1' || map[y][x + 1] == '5')) \
		|| ((map[y - 1][x] == '1' || map[y - 1][x] == '5') \
		&& (map[y + 1][x] == '0' || map[y + 1][x] == '2')) \
		|| ((map[y + 1][x] == '1' || map[y + 1][x] == '5') \
		&& (map[y - 1][x] == '0' || map[y - 1][x] == '0')))
	{
		printf("Line: %d Column: %d => '%c'\n", y, x, map[y][x]);
		exit_free(cube(), 1, "Invalid Use of Portal");
	}
}

void	read_aux(t_cub *cub, t_map *map, int x, int y)
{
	if (!check_zero1(map, map->mtx[y][x], y, x))
		exit_free(cub, 1, "Does not have a wall to support it");
	if (map->mtx[y][x] == '2')
		check_portal(map->mtx, x, y);
	if (map->mtx[y][x] == '5')
		cub->img.wall[5].x ++;
	if (cub->img.wall[5].x > 1)
		exit_free(cub, 1, "Invalid Map Format");
}
