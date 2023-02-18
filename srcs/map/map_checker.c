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

int	read_map(t_cub *cube)
{
	t_map	*map;
	int		i;
	int		j;
	
	map = &cube->map;
	i = -1;
	while (map->mtx[++i])
	{
		j = -1;
		while (map->mtx[i][++j])
		{
			if (map->mtx[i][j] == 'N' || map->mtx[i][j] == 'S' \
			|| map->mtx[i][j] == 'W' || map->mtx[i][j] == 'E')
			{
				map->p_orientation = map->mtx[i][j];
				map->player_x = j;
				map->player_y = i;
				map->num_player++;
			}
		}
	}
	if (map->num_player > 1)
		exit_free(cube, 1, "There can only be one player on the Map");
	return (1);
}
