/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/01 18:18:38 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void    set_line_color(t_cub *cub, t_dist *dist)
{
    int     h;
    int     color;
	
    color = 0xDBACD4;
    if (dist->wallSideY == 1)
        color /= 1.0005;
    h = -1;
	while (++h < cub->render_img.floorPoint)
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, cub->img.colors[0]);
    h--;
	while (++h < cub->render_img.ceilingPoint)
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, color);
    h--;
	while (++h < screenH)
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, cub->img.colors[1]);
}

void    get_wall_h(t_cub *cub, t_dist *dist)
{
    double  fisheyeDist;
    double  wallHeight;

    if (dist->wallSideY == 0)
        fisheyeDist = dist->sideDistX - dist->deltaDistX;
    else
        fisheyeDist = dist->sideDistY - dist->deltaDistY;
    wallHeight = (int)(screenH / fisheyeDist) / 1.2;
    // printf("lineH %f floor %d ceiling%d\n", wallHeight, cub->render_img.floorPoint, cub->render_img.ceilingPoint);
    cub->render_img.floorPoint = screenH / 2 - wallHeight / 2;
    if (cub->render_img.floorPoint < 0)
        cub->render_img.floorPoint = 0;
    cub->render_img.ceilingPoint = screenH / 2 + wallHeight / 2;
    if (cub->render_img.ceilingPoint >= screenH)
        cub->render_img.ceilingPoint = screenH - 1;
    // printf("dirY %f dirX %f\n", cub->player.dirY, cub->player.dirX);

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
            dist->wallSideY = 0;
        }
        else
        {
            dist->sideDistY += dist->deltaDistY;
            dist->mapY += dist->stepY;
            dist->wallSideY = 1;
        }
        if (mtx[dist->mapX][dist->mapY] == '1')
            hit = 1;
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
    // printf("sideX %f sideY %f\n", dist->sideDistX, dist->sideDistY);
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
        // printf("rayX %f rayY %f\n", dist.raydirY, dist.raydirX);
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
        // printf("delta X %f deltaY %f\n", dist.deltaDistX, dist.deltaDistY);
        calc_sidedist(cub, &dist);
        check_ray_hit(cub, &dist);
        get_wall_h(cub, &dist);
        set_line_color(cub, &dist);
    }
        render_screen(cub);
        printf("dirY %f dirX %f\n", cub->player.dirY, cub->player.dirX);
}   
