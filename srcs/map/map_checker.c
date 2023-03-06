/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:42:49 by mgranate          #+#    #+#             */
/*   Updated: 2023/03/06 17:09:05 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_map_elements(t_cub *cub)
{
	if (!cub->map.p_orientation)
		exit_free(cub, 1, "Map does not contain a Player");
	if (cub->map.num_player > 1)
		exit_free(cub, 1, "Map can only contain one Player");
}

static int    checker_zero(char **map, int y, int x)
{
	if ((y - 1) < 0)
		return (0);
    if (!map[y - 1][x] || !map[y][x - 1] || !map[y + 1][x] || !map[y][x + 1]\
    || !map[y + 1][x + 1] || !map[y - 1][x - 1] || !map[y + 1][x - 1]\
	|| !map[y - 1][x + 1])
        return (0);
    if (map[y - 1][x] == ' ' || map[y][x - 1] == ' ' || map[y + 1][x] == ' '\
	|| map[y][x + 1] == ' ' || map[y + 1][x + 1]  == ' ' || map[y - 1][x - 1] == ' ' \
	|| map[y + 1][x - 1] == ' ' || map[y - 1][x + 1] == ' ')
	{
        return (0);
	}
	if (map[y - 1][x] == '\n' || map[y][x - 1] == '\n' || map[y + 1][x] == '\n' 	\
	|| map[y][x + 1] == '\n' || map[y + 1][x + 1]  == '\n' || map[y - 1][x - 1] == '\n' \
	|| map[y + 1][x - 1] == '\n' || map[y - 1][x + 1] == '\n')
        return (0);
    return (1);
}

static void	add_player_atributes(t_map *map, int x, int y)
{
	map->p_orientation = map->mtx[y][x];
	map->player_x = x;
	map->player_y = y;
	map->num_player++;
}

static int	check_zero1(t_map *map, char c, int y, int x)
{
	if (c == '0')
    	if (!checker_zero(map->mtx, y, x))
		{
            printf("Line: %d Column: %d => '%c' \n", y, x, c);
			return (0);
		}
	return (1);
}

void	read_map(t_cub *cub)
{
	t_map	*map;
	int		y;
	int		x;
	
	map = &cub->map;
	y = -1;
	while (map->mtx[++y])
	{
		x = -1;
		while (map->mtx[y][++x])
		{
			if (map->mtx[y][x] == 'N' || map->mtx[y][x] == 'S' \
			|| map->mtx[y][x] == 'W' || map->mtx[y][x] == 'E')
				add_player_atributes(map, x, y);
            else if (map->mtx[y][x] != '0' && map->mtx[y][x] != '1' && map->mtx[y][x] \
            != ' ' && map->mtx[y][x] != '\n' && map->mtx[y][x] != '2')
            {
                printf("Line: %d Column: %d => '%c' \n", y, x, map->mtx[y][x]);
                exit_free(cub, 1, "Not a valid  character on the Map");
            }
			if (!check_zero1(map, map->mtx[y][x], y, x))
				exit_free(cub, 1, "Does not have a wall to support it");
		}
	}
}
