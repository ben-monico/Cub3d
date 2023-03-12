/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:49:04 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/11 17:49:04 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void put_player(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 6)
	{
		x = -1;
		while (++x < 6)
			my_mlx_pixel_put(&cub->screen, MINIMAP_W / 2 + x + 5, \
			MINIMAP_W / 2 + y + 5, 0x008fb3);
	}
}

int	get_clr(char c)
{
	if (c == '1' || c == '5')
		return (0x414141);
	else if (c == '2')
		return (0x116611);
	else if (c == '3')
		return (0x11DD11);
	else
		return (0xFFFFFF);
}
void	new_minimap(t_cub *cub, char **mtx, double iter)
{
	double	x;
	double	y;
	int		i;
	int		j;

	y = cub->player.pos_x - MINIMAP_H / 100 * 2;
	i = -1;
	while (++i < MINIMAP_H)
	{
		j = -1;
		x = cub->player.pos_y - (MINIMAP_W / 100 * 2);
		while (++j < MINIMAP_W)
		{
			if (y < 0 || x < 0 || x > string().len(mtx[(int)y], 0) ||\
			((mtx[(int)y][(int)x] < '0' || mtx[(int)y][(int)x] > '5')))
			{
				x += iter;
				continue ;
			}
			my_mlx_pixel_put(&cub->screen, j, i, get_clr(mtx[(int)y][(int)x]));
			x += iter;
		}
		y += iter;
	}
	put_player(cub);
}