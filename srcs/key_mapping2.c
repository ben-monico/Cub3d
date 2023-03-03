/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:14:22 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/03 17:30:38 by mgranate         ###   ########.fr       */
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

// void mouse_move(int x, int y, t_cub *cub)
// {
//     double  
// }

void p_rotation(t_player *player, double angle)
{
    double  x;
    double  y;

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

void    verify_collision_and_door(t_cub *cub, double x, double y)
{
    double  col;
    char    **mtx;

    mtx = cub->map.mtx;
    col = 0.5;
    if (mtx[(int)x][(int)cub->player.posY] != '1')
        cub->player.posX = x;
    if (mtx[(int)cub->player.posX][(int)y] != '1')
        cub->player.posY = y;
    x = -1;
    while(mtx[(int)++x])
    {
        y = -1;
        while (mtx[(int)x][(int)++y])
        {
            if (mtx[(int)x][(int)y] == '3')
                mtx[(int)x][(int)y] = '2';
        }
    }
    if (mtx[(int)(cub->player.posX)][(int)cub->player.posY] == '2')
        mtx[(int)(cub->player.posX)][(int)cub->player.posY] = '3';
    if (mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] == '2')
        mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] = '3';
    if (mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] == '2')
        mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] = '3';
    if (mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] == '2')
        mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] = '3';
    if (mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] == '2')
        mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] = '3';
}