/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:26:10 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 23:26:35 by mgranate_ls      ###   ########.fr       */
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
    cub->player.fovX = 0.66;
	cub->player.dirX = 0;
	cub->player.dirY = 0;
	x = -1;
    while(mtx[++x])
    {
        y = -1;
        while (mtx[x][++y])
        {
            if (mtx[x][y] == 'N' || mtx[x][y] == 'S'
			|| mtx[x][y] == 'E' || mtx[x][y] == 'W')
            {
				printf("oi\n");
                cub->player.posX = x;
                cub->player.posY = y;
				printf("x %d y %d\n", x, y);

				if (mtx[x][y] == 'N')
            	    cub->player.dirY = 1;
				else if (mtx[x][y] == 'S')
					 cub->player.dirY = -1;
				else if (mtx[x][y] == 'E')
					 cub->player.dirX = -1;
				else
					 cub->player.dirX = 1;
				return ;
            }
        }
    }
}