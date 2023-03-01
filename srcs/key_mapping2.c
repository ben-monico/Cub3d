/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:14:22 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/01 13:47:02 by bcarreir         ###   ########.fr       */
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

int check_collision(t_cub *cub, double x, double y)
{
    double  col;
    int     yy;
    int     i;
    int     j;

    col = 0.3;
    x -= col;
    i = -1;
    j = -1;
    while (++i < 2)
    {
        yy = y - col;
        while(++j < 2)
        {
            if (cub->map.mtx[(int)x][(int)y] == '1')
                return (1);
            yy += col;
        }
        x += col;
    }
    return (0);
}
