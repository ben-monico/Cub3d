/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/27 18:31:57 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void    put_line(t_cub *cub, t_dist *dist)
{
    int     h;
    int     color;
	
    color = 0x840036;
    if (dist->wallSideY == 1)
        color /= 1.5;
    printf("floor %d / ceiling %d x%d\n", cub->line.floorPoint, cub->line.ceilingPoint, cub->line.x);
	h = 0;
	while (h < cub->line.ceilingPoint - cub->line.floorPoint)
	{
       
		my_mlx_pixel_put(&cub->line, 1, h, color);
		h++;
        // printf("linha posta %d\n", h);
	}
    printf("X = %d\n", line->x);
    printf("%f %f\n", cub->player.dirX, cub->player.dirX);
    mlx_put_image_to_window(cub->mlx, cub->win, imgline.ptr, line->x, line->floorPoint); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cub. Try changing its values to check different coordinates.
}

void    get_wall_h(t_cub *cub, t_dist *dist)
{
    double  fisheyeDist;
    double     wallHeight;

    if (dist->wallSideY == 0)
        fisheyeDist = dist->sideDistX - dist->deltaDistX;
    else
        fisheyeDist = dist->sideDistY - dist->deltaDistY;
    wallHeight = (int)screenH / fisheyeDist;
    line->floorPoint = (screenH - wallHeight) / 2;
    if (wallHeight > screenH)
        line->ceilingPoint = 0;
    line->floorPoint = screenH - line->ceilingPoint;
    printf("lineH %f floor %d ceiling%d \n", wallHeight, line->floorPoint, line->ceilingPoint);
    if (line->floorPoint < 0)
        line->floorPoint = 0;
    if (line->ceilingPoint >= screenH)
        line->ceilingPoint = screenH - 1;

}

void    check_ray_hit(t_cub *cub, t_dist *dist)
{
    int hit;
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
        if (mtx[dist->mapX][dist->mapY] != 0)
            hit = 1;
    }
}

void    calc_sidedist(t_cub *cub, t_dist *dist)
{
    if (dist->rayDirX < 0)
    {
        dist->stepX = -1;
        dist->sideDistX = (cub->player.posX - dist->mapX) * dist->deltaDistX;
    }
    else
    {
        dist->stepX = 1;
        dist->sideDistX = (dist->mapX + 1 - cub->player.posX) * dist->deltaDistX;
    }
    if (dist->rayDirY < 0)
    {
        dist->stepY = -1;
        dist->sideDistY = (cub->player.posY - dist->mapY) * dist->deltaDistY;
    }
    else
    {
        dist->stepY = 1;
        dist->sideDistY = (dist->mapY + 1 - cub->player.posY) * dist->deltaDistY;
    }
    printf("sideX %f sideY %f\n", dist->sideDistX, dist->sideDistY);
}

void    raycasting(t_cub *cub)
{
    t_dist  dist;
    t_line  line;
    double  cameraX;

    line.x = -1;
    while (++line.x < screenW)
    {
        cameraX = 2 * line.x / (double)screenW - 1;
        dist.rayDirX = cub->player.dirX + -cub->player.fovX * cameraX;
        dist.rayDirY = cub->player.dirY + -cub->player.fovY * cameraX;
        printf("rayX %f rayY %f\n", dist.rayDirX, dist.rayDirY);
        dist.mapX = (int)cub->player.posX;
        dist.mapY = (int)cub->player.posY;
        if (dist.rayDirX == 0)
            dist.deltaDistX = 1e30;
        else
            dist.deltaDistX = fabs(1 / dist.rayDirX);
        if (dist.rayDirY == 0)
            dist.deltaDistY = 1e30;
        else
           dist.deltaDistY = fabs(1 / dist.rayDirY);
        printf("delta X %f deltaY %f\n", dist.deltaDistX, dist.deltaDistY);
        calc_sidedist(cub, &dist);
        check_ray_hit(cub, &dist);
        get_wall_h(cub, &dist);
        put_line(cub, &dist);
    }
}   
