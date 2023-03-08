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

int	toggle_portal(double x, double y, char get, char set)
{
	t_cub	*cub;
	char	**mtx;
	int		i;

	cub = new_cube();
	mtx = cub->map.mtx;
	i = 0;
	while(++i <= 4)
	{
		if (mtx[(int)x][(int)y] == get)
		{
			mtx[(int)x][(int)y] = set;
			return (1);
		}
		x = cub->player.posX + cub->player.dirY * DUB_STEP * 10 * i;
		y = cub->player.posY + cub->player.dirX * DUB_STEP * 10 * i;
	}
	return(0);
}

void open_portal(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.posX + cub->player.dirY * DUB_STEP * 10;
	y = cub->player.posY + cub->player.dirX * DUB_STEP * 10;
	if (toggle_portal(x, y, '2', '3'))
		return ;
	toggle_portal(x, y, '3', '2');
}