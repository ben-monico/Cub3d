/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:14:22 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/01 17:04:34 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void arrow_left_press(t_cub *cub)
{
    p_rotation(&cub->player, -5);
    raycasting(cub);
}

void arrow_right_press(t_cub *cub)
{
    p_rotation(&cub->player, 5);
    raycasting(cub);
}

void p_rotation(t_player *player, double angle)
{
    double  x;
    double  y;
    double  olddirY;
    double  olddirX;

    olddirY = player->dirY;
    olddirX = player->dirX;
    angle *= M_PI / 180;
    x = player->dirY * cos(angle) + player->dirX * sin(angle);
    y = player->dirY * -sin(angle) + player->dirX * cos(angle);
    player->dirY = x;
    player->dirX = y;
    x = player->fovX * cos(angle) + player->fovY * sin(angle);
    y = player->fovX * -sin(angle) + player->fovY * cos(angle);  
    player->fovX = x;
    player->fovY = y;  
}

void    verify_collision(t_cub *cub, double x, double y)
{
    printf("x = %d, y = %d, mtx%c\n", (int)x,(int)y, cub->map.mtx[(int)x][(int)y] );
		if  (cub->map.mtx[(int)x][(int)cub->player.posY] != '1')
        {
    		cub->player.posX = x;
        }
        if  (cub->map.mtx[(int)cub->player.posX][(int)y] != '1')
        {
            cub->player.posY = y;
        }	
}