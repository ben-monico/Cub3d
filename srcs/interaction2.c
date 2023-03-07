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

void open_portal(t_cub *cub, char **mtx)
{
	double	col;
	double	x;
	double	y;
	int		i;
	int		j;

	col = 1;
	x = cub->player.posX - col;
	j = -1;
	while(++j < 3)
	{
		i = -1;
		y = cub->player.posY - col;
		while(++i < 3)
		{
			if (mtx[(int)x][(int)y] == '2')
			{
				mtx[(int)x][(int)y] = '3';
				return ; 
			}
			y += col;
		}
		x += col;
	}
	x = cub->player.posX - col;
	j = -1;
	while(++j < 3)
	{
		i = -1;
		y = cub->player.posY - col;
		while(++i < 3)
		{
			if ((int)cub->player.posX == '3' && (int)cub->player.posY == '3' && mtx[(int)x][(int)y] == '3' && round(x) == round(cub->player.posX) && round(y) == round(cub->player.posY))
				continue ;
			if (mtx[(int)x][(int)y] == '3' )
			{
				mtx[(int)x][(int)y] = '2';
				return ; 
			}
			y += col;
		}
		x += col;
	}
	// if (mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] == '2')
	// {
    //     mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] = '3';
	// 	return ;
	// }
    // if (mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] == '2')
    // {
    // 	mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] = '3';
	// 	return ;
	// }
    // if (mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] == '2')
	// {
    //     mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] = '3';
	// 	return ;
	// }
	// if (mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] == '2')
	// {
    //     mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] = '3';
	// 	return ;
	// }
	// if (mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] == '3')
	// {
    //     mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] = '2';
	// 	return ;
	// }
    // if (mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] == '3')
    // {
    // 	mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] = '2';
	// 	return ;
	// }
    // if (mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] == '3')
	// {
    //     mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] = '2';
	// 	return ;
	// }
	// if (mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] == '2')
	// {
    //     mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] = '3';
	// 	return ;
	// }
}