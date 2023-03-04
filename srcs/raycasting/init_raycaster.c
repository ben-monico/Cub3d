/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:26:10 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/01 18:58:32 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_raycast_vars(t_cub *cub)
{
	char	**mtx;
	int		x;
    int		y;
	  
	mtx = cub->map.mtx;
    cub->player.fovX = 0;
    cub->player.fovY = 0;
	cub->player.dirY = 0;
	cub->player.dirX = 0;
	x = -1;
    while(mtx[++x])
    {
        y = -1;
        while (mtx[x][++y])
        {
            if (mtx[x][y] == 'N' || mtx[x][y] == 'S'
			|| mtx[x][y] == 'E' || mtx[x][y] == 'W')
            {
                cub->player.posX = x + 0.5;
                cub->player.posY = y + 0.5;
				if (mtx[x][y] == 'E')
				{
            	    cub->player.dirX = 1;
					cub->player.fovX = 0.66;
				}
				else if (mtx[x][y] == 'W')
				{
					cub->player.dirX = -1;
					cub->player.fovX = -0.66;
				}
				else if (mtx[x][y] == 'S')
				{
					 cub->player.dirY = 1;
					 cub->player.fovY = -0.66;
				}
				else if (mtx[x][y] == 'N')
				{
					cub->player.dirY = -1;
					cub->player.fovY = 0.66;
				}
				mtx[x][y] = '0';
				return ;
            }
        }
    }
}