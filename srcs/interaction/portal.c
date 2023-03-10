/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:09:58 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/07 22:09:58 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	check_portal_x(t_cub *cub, char **mtx, double x, double y)
{
	if (floor(x) > floor(cub->player.pos_x))
	{
		while (mtx[(int)(x + 1)][(int)y] == '3')
			++x;
		cub->player.pos_x = floor(x) + 1.2;
		cub->player.pos_y = floor(y) + 0.5;
	}
	else if (floor(x) < floor(cub->player.pos_x))
	{
		while (mtx[(int)(x - 1)][(int)y] == '3')
			--x;
		cub->player.pos_x = floor(x) - 0.2;
		cub->player.pos_y = floor(y) + 0.5;
	}
}

int	portal_teleport(t_cub *cub, char **mtx, double x, double y)
{
	if (floor(y) > floor(cub->player.pos_y))
	{
		while (mtx[(int)x][(int)(y + 1)] == '3')
			++y;
		cub->player.pos_y = floor(y) + 1.2;
		cub->player.pos_x = floor(x) + 0.5;
	}
	else if (floor(y) < floor(cub->player.pos_y))
	{
		while (mtx[(int)x][(int)(y - 1)] == '3')
			--y;
		cub->player.pos_y = floor(y) - 0.2;
		cub->player.pos_x = floor(x) + 0.5;
	}
	check_portal_x(cub, mtx, x, y);
	return (1);
}

void	find_tunnel(double x, double y, char get, char set)
{
	t_cub	*cub;
	char	**mtx;

	cub = cube();
	mtx = cub->map.mtx;
	mtx[(int)x][(int)y] = set;
	while (mtx[(int)x + 1][(int)y] == get)
		mtx[(int)++x][(int)y] = set;
	while (mtx[(int)x - 1][(int)y] == get)
		mtx[(int)--x][(int)y] = set;
	while (mtx[(int)x][(int)y + 1] == get)
		mtx[(int)x][(int)++y] = set;
	while (mtx[(int)x][(int)y - 1] == get)
		mtx[(int)x][(int)--y] = set;
}

int	toggle_portal(double x, double y, char get, char set)
{
	t_cub	*cub;
	char	**mtx;
	int		i;

	cub = cube();
	mtx = cub->map.mtx;
	i = 0;
	while (++i <= 4)
	{
		if (mtx[(int)x][(int)y] == get)
		{
			find_tunnel(x, y, get, set);
			return (1);
		}
		x = cub->player.pos_x + cub->player.dir_y * DUB_STEP * 10 * i;
		y = cub->player.pos_y + cub->player.dir_x * DUB_STEP * 10 * i;
	}
	return (0);
}

void	open_portal(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.pos_x + cub->player.dir_y * DUB_STEP * 10;
	y = cub->player.pos_y + cub->player.dir_x * DUB_STEP * 10;
	if (toggle_portal(x, y, '2', '3'))
		return ;
	toggle_portal(x, y, '3', '2');
}
