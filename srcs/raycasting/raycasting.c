/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/23 20:30:19 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void    put_line(t_cub *cub, t_line *line, t_dist *dist)
{
    t_img   imgline;
    int     h;
    int     color;
	
    imgline.ptr = mlx_new_image(cub->mlx, 1, screenH);
	imgline.addr = mlx_get_data_addr(imgline.ptr, &imgline.bpp,
                    &imgline.size_line, &imgline.endian);
    printf("floor %d / ceiling %d x%d\n", line->floorPoint, line->ceilingPoint, line->x);
	h = 0;
	while (h < line->ceilingPoint - line->floorPoint)
	{
        color = 0x840036;
        if (dist->wallSide == 1)
            color /= 1.5;
		my_mlx_pixel_put(&imgline, 1, h, color);
		h++;
        // printf("linha posta %d\n", h);
	}
    printf("X = %d\n", line->x);
    mlx_put_image_to_window(cub->mlx, cub->win, imgline.ptr, line->x, line->floorPoint); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cub. Try changing its values to check different coordinates.
}

void    fix_fisheye_get_wall_h(t_cub *cub, t_dist *dist, t_line *line)
{
    double  fisheyeDist;
    int     wallHeight;

    if (dist->wallSide == 0)
        fisheyeDist = dist->sideDistX - dist->deltaDistX;
    else
        fisheyeDist = dist->sideDistY - dist->deltaDistY;
    printf("fisheye %f\n", fisheyeDist);
    wallHeight = (int)(screenH / fisheyeDist);
    line->floorPoint = -wallHeight / 2 + screenH / 2;
    line->ceilingPoint = wallHeight / 2 + screenH / 2;
    printf("floor %d ceiling%d \n", line->floorPoint, line->ceilingPoint);
    if (line->floorPoint < 0)
        line->floorPoint = 0;
    if (line->ceilingPoint >= screenH)
        line->ceilingPoint = screenH - 1;
    put_line(cub, line, dist);

}

void    perform_DDA(t_dist *dist, t_cub *cub, t_line *line)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (dist->sideDistX < dist->sideDistY)
        {
            dist->sideDistX += dist->deltaDistX;
            dist->mapX += dist->stepX;
            dist->wallSide = 0;
        }
        else
        {
            dist->sideDistY += dist->deltaDistY;
            dist->mapY += dist->stepY;
            dist->wallSide = 1;
        }
        // if (check_map().[dist->mapX][dist->mapY] > 0)
        //     hit = 1;
        printf("mapx %d mapy %d\n", dist->mapX, dist->mapY);
        if (cub->map.mtx[dist->mapX][dist->mapY] > 0)
            hit = 1;
    }
    fix_fisheye_get_wall_h(cub, dist, line);
}

void    calc_sidedist(t_dist *dist, t_cub *cub, t_line *line)
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
    perform_DDA(dist, cub, line);
    printf("sideX %f sideY %f\n", dist->sideDistX, dist->sideDistY);
}

void    raycasting(t_cub *cub)
{
    double  cameraX;
    t_dist  dist;
    t_line  line;
    
    line.x = -1;
    while (++line.x < screenW)
    {
        cameraX = 2 * line.x / (double)screenW - 1;
        dist.rayDirX = cub->player.dirX + cub->player.fovX * cameraX;
        dist.rayDirY = cub->player.dirY + cub->player.fovY * cameraX;
        printf("rayX %f rayY %f\n", dist.rayDirX, dist.rayDirY);
        dist.mapX = (int)cub->player.posX;
        dist.mapY = (int)cub->player.posY;
                printf("mapx %d mapy %d\n", dist.mapX, dist.mapY);
        if (dist.rayDirX == 0)
            dist.deltaDistX = 1e30;
        else
            dist.deltaDistX = fabs(1 / dist.rayDirX);
        if (dist.rayDirY == 0)
            dist.deltaDistY = 1e30;
        else
           dist.deltaDistY = fabs(1 / dist.rayDirY);
        printf("delta X %f deltaY %f\n", dist.deltaDistX, dist.deltaDistY);
        calc_sidedist(&dist, cub, &line);
    }
}   
