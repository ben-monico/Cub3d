/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/17 18:21:54 by benmonico        ###   ########.fr       */
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
    printf("floor %d / ceiling %d x%d\n", line->x, line->ceilingPoint, line->x);
	while (h < line->ceilingPoint)
	{
		my_mlx_pixel_put(&imgline, line->x, h, 0xFFFFFF);
		h++;
        // printf("linha posta %d\n", h);
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
    line->floorPoint = -wallHeight / 2 + screenH / 2;
    line->ceilingPoint = wallHeight / 2 + screenH / 2;
    if (line->floorPoint < 0)
        line->floorPoint = 0;
    if (line->ceilingPoint >= screenH)
        line->ceilingPoint = screenH - 1;
    printf("fisheye%f\n", fisheyeDist);
    
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
        // if (check_map()[dist->mapX][dist->mapY] > 0)
        //     hit = 1;
        if (map->map[dist->mapX][dist->mapY] > 0)
            hit = 1;
    }    
}

void    raycasting2(t_cub *cub, t_player *player)
{
    double  cameraX;
    t_dist  dist;
    t_line  line;
    //placeholder
      t_map map = tester_map();
     
        int x = 0;
        int y;
        while(map.map[x])
        {
            y = 0;
            while (map.map[x][y])
            {
                if (map.map[x][y] == 'N')
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
    player->fovX = 0;
    player->fovX = 66;
    line.x = -1;
    while (++line.x < screenW)
    {
        cameraX = 2 * line.x / (double)screenW - 1;
        dist.rayDirX = player->dirX + player->fovX * cameraX;
        dist.rayDirY = player->dirY + player->fovY * cameraX;
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
        printf("h %d\n", line.x);
        calc_sidedist(&dist, player);
        perform_DDA(&dist, &map);
        fix_fisheye_get_wall_h(&dist, &line);
        put_line(cub, &line);
    }
}   

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void    raycasting(t_cub *cub, t_player *player)
{
    (void)player;
double posX = 22, posY = 12;  //x and y start position
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

//   double time = 0; //time of current frame
//   double oldTime = 0; //time of previous frame


  while(1)
  {
    for(int x = 0; x < 25; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)screenW - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(screenH / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenH / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + screenH / 2;
      if(drawEnd >= screenH) drawEnd = screenH - 1;

      //give x and y sides different brightness
    //   if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      t_img   imgline;
    int     has;

    imgline.ptr = mlx_new_image(cub->mlx, 1, screenH);
	imgline.addr = mlx_get_data_addr(imgline.ptr, &imgline.bpp,
                    &imgline.size_line, &imgline.endian);
	has = drawStart;
	while (has < (drawEnd / drawStart) / 2)
	{
        // printf("x %d h %d s%d e%d\n", x,has, drawStart, drawEnd);
		my_mlx_pixel_put(&imgline, x, has, 0x00FFFFFF);
        mlx_put_image_to_window(cub->mlx, cub->win, imgline.ptr, x, has);
		has++;
	}
    }
  }
}