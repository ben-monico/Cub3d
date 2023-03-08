/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/08 13:07:29 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void    get_wall_h(t_cub *cub, t_dist *dist)
{
    if (dist->wallSideX == 0)
        dist->fisheyeDist = dist->sideDistX - dist->deltaDistX;
    else
         dist->fisheyeDist = dist->sideDistY - dist->deltaDistY;
    if (dist->wallSideX == 0)
		dist->wallX = cub->player.posY + dist->fisheyeDist * dist->raydirX;
	else
		dist->wallX = cub->player.posX + dist->fisheyeDist * dist->raydirY;
	dist->wallX -= floor((dist->wallX));
    cub->render_img.wallHeight = (int)(screenH /  dist->fisheyeDist) / 1;
    cub->render_img.floorPoint = screenH / 2 - cub->render_img.wallHeight / 2;
    cub->render_img.ceilingPoint = screenH / 2 + cub->render_img.wallHeight / 2;
}

void    check_ray_hit(t_cub *cub, t_dist *dist)
{
    int     hit;
    char    **mtx;

    mtx = cub->map.mtx;
    hit = 0;
    while (hit == 0)
    {
        if (dist->sideDistX < dist->sideDistY)
        {
            dist->sideDistX += dist->deltaDistX;
            dist->mapX += dist->stepX;
            dist->wallSideX = 0;
        }
        else
        {
            dist->sideDistY += dist->deltaDistY;
            dist->mapY += dist->stepY;
            dist->wallSideX = 1;
        }
        if (mtx[dist->mapX][dist->mapY] == '1' || mtx[dist->mapX][dist->mapY] == '2' || mtx[dist->mapX][dist->mapY] == '3')
        {
            hit = 1;
            cub->player.obj_hit = mtx[dist->mapX][dist->mapY];
        }
    }
}

void    calc_sidedist(t_cub *cub, t_dist *dist)
{
    if (dist->raydirY < 0)
    {
        dist->stepX = -1;
        dist->sideDistX = (cub->player.posX - dist->mapX) * dist->deltaDistX;
    }
    else
    {
        dist->stepX = 1;
        dist->sideDistX = (dist->mapX + 1 - cub->player.posX) * dist->deltaDistX;
    }
    if (dist->raydirX < 0)
    {
        dist->stepY = -1;
        dist->sideDistY = (cub->player.posY - dist->mapY) * dist->deltaDistY;
    }
    else
    {
        dist->stepY = 1;
        dist->sideDistY = (dist->mapY + 1 - cub->player.posY) * dist->deltaDistY;
    }
}

void    raycasting(t_cub *cub)
{
    t_dist  dist;
    double  cameraX;

    cub->render_img.x = -1;
    while (++cub->render_img.x < screenW)
    {
        cameraX = 2 * cub->render_img.x / (double)screenW - 1;
        dist.raydirY = cub->player.dirY + cub->player.fovX * cameraX;
        dist.raydirX = cub->player.dirX + cub->player.fovY * cameraX;
        dist.mapX = (int)cub->player.posX;
        dist.mapY = (int)cub->player.posY;
        if (dist.raydirY == 0)
            dist.deltaDistX = 1e30;
        else
            dist.deltaDistX = fabs(1 / dist.raydirY);
        if (dist.raydirX == 0)
            dist.deltaDistY = 1e30;
        else
           dist.deltaDistY = fabs(1 / dist.raydirX);
        calc_sidedist(cub, &dist);
        check_ray_hit(cub, &dist);
        get_wall_h(cub, &dist);
        set_line_color(cub, &dist, dist.wallX * cub->img.wall[0].width);
    }
    render_screen(cub);
}   
