/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:42:49 by mgranate          #+#    #+#             */
/*   Updated: 2023/03/08 22:17:46 by mgranate_ls      ###   ########.fr       */
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

int	check_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

static void	add_player_atributes(t_map *map, int x, int y)
{
	map->p_orientation = map->mtx[y][x];
	map->player_x = x;
	map->player_y = y;
	map->num_player++;
}

int	check_zero1(t_map *map, char c, int y, int x)
{
	if (c == '0' || c == '2')
	{
		if (!checker_zero(map->mtx, y, x))
		{
			printf("Line: %d Column: %d => '%c' \n", y, x, c);
			return (0);
		}
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
			else if (map->mtx[y][x] != '0' && map->mtx[y][x] != '1' \
			&& map->mtx[y][x] != ' ' && map->mtx[y][x] != '\n' \
			&& map->mtx[y][x] != '2')
			{
				printf("Line: %d Column: %d => '%c' \n", y, x, map->mtx[y][x]);
				exit_free(cub, 1, "Not a valid  character on the Map");
			}
			read_aux(cub, map, x, y);
		}
	}
}
