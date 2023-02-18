/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/18 00:31:45 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
//missing map getter
t_map		map;

void    put_line(t_cub *cub, t_line *line)
{
    t_img   imgline;
    int     h;

    imgline.ptr = mlx_new_image(cub->mlx, 1, line->ceilingPoint);
	imgline.addr = mlx_get_data_addr(imgline.ptr, &imgline.bpp,
                    &imgline.size_line, &imgline.endian);
	h = line->floorPoint;
    printf("floor %d / ceiling %d\n", line->floorPoint, line->ceilingPoint);
	while (h < line->ceilingPoint)
	{
		my_mlx_pixel_put(&imgline, line->x, h, 0x0000FF);
		h++;
        printf("linha posta %d\n", h);
	}
}

void    fix_fisheye_get_wall_h(t_dist *dist, t_line *line)
{
    double  fisheyeDist;
    int     wallHeight;

    if (dist->wallSide == 0)
        fisheyeDist = dist->sideDistX - dist->deltaDistX;
    else
        fisheyeDist = dist->sideDistY - dist->deltaDistY;
    wallHeight = (int)(screenH / fisheyeDist);
    line->ceilingPoint = -wallHeight / 2 + screenH / 2;
    line->floorPoint = wallHeight / 2 + screenH / 2;
    if (line->ceilingPoint < 0)
        line->floorPoint = 0;
    if (line->floorPoint >= screenH)
        line->floorPoint = screenH - 1;
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
}

void    perform_DDA(t_dist *dist, t_map *map)
{
    int hit;

    hit = 0;
    while (!hit)
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
        // if (check_map()[dist->mapX][dist->mapY] > 0)
        //     hit = 1;
        if (map->mtx[dist->mapX][dist->mapY] > 0)
            hit = 1;
    }    
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
                    player->dirX = 0;
                    player->dirY = 1;
                }
                y++;  
            }
            x++;
        }
    //end of placeholder

    while (++line.x < screenW)
    {
        cameraX = 2 * line.x / (double)screenW - 1;
        dist.rayDirX = player->dirX + player->fovX * cameraX;
        dist.rayDirY = player->dirY + player->fovY * cameraX;
    }
    dist.mapX = (int)player->posX;
    dist.mapY = (int)player->posY;
    if (dist.rayDirX == 0)
        dist.deltaDistX = 1e30;
    else
        dist.deltaDistX = fabs(1/dist.rayDirX);
    if (dist.rayDirY == 0)
        dist.deltaDistY = 1e30;
    else
       dist.deltaDistY = fabs(1/dist.rayDirY);
    calc_sidedist(&dist, player);
    perform_DDA(&dist, &map);
    fix_fisheye_get_wall_h(&dist, &line);
    put_line(cub, &line);

}