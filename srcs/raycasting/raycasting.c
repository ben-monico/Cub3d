/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/22 17:37:17 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
//missing map getter
t_map		map;

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
    mlx_put_image_to_window(cub->mlx, cub->win, imgline.ptr, line->x, line->floorPoint); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cube. Try changing its values to check different coordinates.
}

void    fix_fisheye_get_wall_h(t_dist *dist, t_line *line)
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
    
}

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
    printf("sideX %f sideY %f\n", dist->sideDistX, dist->sideDistY);
}

void    perform_DDA(t_dist *dist, t_map *map)
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
        if (map->mtx[dist->mapX][dist->mapY] > 0)
            hit = 1;
    }    
}

void    draw_celingfloor(t_cub *cube)
{
    t_img floor;
    
	floor.ptr = mlx_new_image(cube->mlx, screenW, screenH / 8);
	floor.addr = mlx_get_data_addr(floor.ptr, &floor.bpp, &floor.size_line, &floor.endian);
	int h,w;
	h = 0;
	while (h < screenH / 8)
	{
		w = 0;
		while (w < screenW)
		{
			my_mlx_pixel_put(&floor, w, h, abs(cube->img.colors[0]));
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, floor.ptr, 0, screenH / 2);
	h = 0;
	while (h < screenH / 8)
	{
		w = 0;
		while (w < screenW)
		{
			my_mlx_pixel_put(&floor, w, h, abs(cube->img.colors[1]));
			w++;
		}
		h++;
	} // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cube. Try changing its values to check different coordinates.
		mlx_put_image_to_window(cube->mlx, cube->win, floor.ptr, 0, 0);
}

void    raycasting(t_cub *cub, t_player *player)
{
    double  cameraX;
    t_dist  dist;
    t_line  line;
    
    //placeholder
      t_map map;
	  
	  map = cub->map;
     
        int x = 0;
        int y;
        while(map.mtx[x])
        {
            y = 0;
            while (map.mtx[x][y])
            {
                if (map.mtx[x][y] == 'N')
                {
                    player->posX = x;
                    player->posY = y;
                    player->dirX = 1;
                    player->dirY = 0;
                }
                y++;  
            }
            x++;
        }
    //end of placeholder
    
    player->fovX = 0;
    player->fovX = 0.66;
    line.x = 0;
    while (line.x < screenW)
    {
        cameraX = 2 * line.x / (double)screenW - 1;
        dist.rayDirX = player->dirX + player->fovX * cameraX;
        dist.rayDirY = player->dirY + player->fovY * cameraX;
        printf("rayX %f rayY %f\n", dist.rayDirX, dist.rayDirY);
        dist.mapX = (int)player->posX;
        dist.mapY = (int)player->posY;
        if (dist.rayDirX == 0)
            dist.deltaDistX = 1e30;
        else
            dist.deltaDistX = fabs(1 / dist.rayDirX);
        if (dist.rayDirY == 0)
            dist.deltaDistY = 1e30;
        else
           dist.deltaDistY = fabs(1 / dist.rayDirY);
        printf("delta X %f deltaY %f\n", dist.deltaDistX, dist.deltaDistY);
        calc_sidedist(&dist, player);
        perform_DDA(&dist, &map);
        fix_fisheye_get_wall_h(&dist, &line);
        draw_celingfloor(cub);
        put_line(cub, &line, &dist);
        line.x++;
    }
}   
