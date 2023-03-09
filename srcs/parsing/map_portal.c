/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_portal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:44:01 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/09 00:30:06 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	if ((map[y][x - 1] == '1' && map[y][x + 1] == '0') \
	|| (map[y][x - 1] == '0' && map[y][x + 1] == '1') \
	|| (map[y - 1][x] == '1' && map[y + 1][x] == '0') \
	|| (map[y + 1][x] == '1' && map[y - 1][x] == '0'))
	{
		printf("Line: %d Column: %d => '%c'\n", y, x, map[y][x]);
		exit_free(new_cube(), 1, "A portal cannot have a path to a Wall");
	}
}

void	read_aux(t_cub *cub, t_map *map, int x, int y)
{
	if (!check_zero1(map, map->mtx[y][x], y, x))
		exit_free(cub, 1, "Does not have a wall to support it");
	if (map->mtx[y][x] == '2')
		check_portal(map->mtx, x, y);
}
