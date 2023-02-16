/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/16 21:17:02 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    calc_sidedist(t_dist *dist, t_player *player)
{
    if (dist->rayDirX < 0)
    {
        dist->stepX = -1;
        dist->sideDistX = (player->posX - dist->mapX) * dist->deltaDistX;
    }
    else
    {
        dist->stepX = 1;
        dist->sideDistX = (dist->mapX + 1 - player->posX) * dist->deltaDistX;
    }
    if (dist->rayDirY < 0)
    {
        dist->stepY = -1;
        dist->sideDistY = (player->posY - dist->mapY) * dist->deltaDistY;
    }
    else
    {
        dist->stepY = 1;
        dist->sideDistY = (dist->mapY + 1 - player->posY) * dist->deltaDistY;
    }
}

void    perform_dda(t_dist *dist)
{
    int hit;
    int side;

    hit = 0;
    while (!hit)
    {
        if (dist->sideDistX < dist->sideDistY)
        {
            dist->sideDistX += dist->deltaDistX;
            dist->mapX += dist->stepX;
            side = 0;
        }
        else
        {
            dist->sideDistY += dist->deltaDistY;
            dist->mapY += dist->stepY;
            side = 1;
        }
        if (check_map()[dist->mapX][dist->mapY] > 0)
            hit = 1;
    }
}

void    raycasting(t_player *player)
{
    int x;
    int w;
    double  cameraX;
    t_dist dist;

    x = -1;
    w = 0;
    while (++x < w)
    {
        cameraX = 2 * x / (double)screenW - 1;
        dist. rayDirX = player->dirX + player->fovX * cameraX;
        dist.rayDirY = player->dirY + player->fovY * cameraX;
    }
    double  perpWallDist;
    int wallside;

    dist.mapX = (int)player->posX;
    dist.mapY = (int)player->posY;
    if (dist.rayDirX == 0)
        dist.deltaDistX = 1e30;
    else
       dist. deltaDistY = abs(1/dist.rayDirY);
    if (dist.rayDirY == 0)
        dist.deltaDistY = 1e30;
    else
       dist. deltaDistY = abs(1/dist.rayDirY);
    calc_sidedist(&dist, player);
    perform_DDA(&dist);
}