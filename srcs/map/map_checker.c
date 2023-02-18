/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:42:49 by mgranate          #+#    #+#             */
/*   Updated: 2023/02/18 02:10:43 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// typedef struct 	s_point {
// 	int			x;				// x : Width  | x-axis
// 	int			y;				// y : Height | y-axis
// }				t_point;
 
// void	fill(char **tab, t_point size, t_point cur, char to_fill)
// {
// 	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
// 		|| tab[cur.y][cur.x] != to_fill)
// 		return ;

// 	tab[cur.y][cur.x] = 'F';
// 	fill(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
// 	fill(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
// 	fill(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
// 	fill(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
// }

// void	flood_fill(char **tab, t_point size, t_point begin)
// {
// 	fill(tab, size, begin, tab[begin.y][begin.x]);
// }

int    checker_zero(char **map, int y, int x)
{
    if (!map[y - 1][x] || !map[y][x - 1] || !map[y + 1][x] || !map[y][x + 1] \
    || !map[y + 1][x + 1] || !map[y - 1][x - 1] || !map[y + 1][x - 1] || !map[y - 1][x + 1])
        return (0);
    //if (map[y - 1][x] == ' ' || map[y][x - 1] == ' ' || map[y + 1][x] == ' ' \
    //|| map[y][x + 1] == ' ' || string().len(map[y + 1], -1) > string().len(map[y], -1))
      //  return(0);
    return (1);
}

int	read_map(t_cub *cube)
{
	t_map	*map;
	int		y;
	int		x;
	
	map = &cube->map;
	y = -1;
	while (map->mtx[++y])
	{
		x = -1;
		while (map->mtx[y][++x])
		{
			if (map->mtx[y][x] == 'N' || map->mtx[y][x] == 'S' \
			|| map->mtx[y][x] == 'W' || map->mtx[y][x] == 'E')
			{
				map->p_orientation = map->mtx[y][x];
				map->player_x = x;
				map->player_y = y;
				map->num_player++;
			}
            else if (map->mtx[y][x] != '0' && map->mtx[y][x] != '1' && map->mtx[y][x] \
            != ' ' && map->mtx[y][x] != '\n')
            {
                printf("Line: %d Column: %d => '%c' \n", y, x, map->mtx[y][x]);
                exit_free(cube, 1, "Not a valid character on the Map");
            }
            if (map->mtx[y][x] == '0')
                if (!checker_zero(map->mtx, y, x))
                {
                    printf("Line: %d Column: %d => '%c' \n", y, x, map->mtx[y][x]);
                    exit_free(cube, 1, "Does not have a wall to support it");
                }
		}
	}
	if (map->num_player > 1)
		exit_free(cube, 1, "There can only be one player on the Map");
	return (1);
}
