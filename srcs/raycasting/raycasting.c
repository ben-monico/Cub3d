/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/06 18:27:20 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
// 	*(unsigned int*)dst = color;
// }
double	calculate_y(t_data *data, float i)
{
    double y;

    y = (float)(i - data->floorPoint) /	(data->ceilingPoint - data->floorPoint) * 64;
    // printf("y = %f\n", y);
	return (y);
}

int get_index(t_cub *cub, t_dist *dist)
{
    if (dist->wallSideX)
    {
        if (cub->player.dirX > 0)
            return (2);
        return (3);
    }
    else
    {
        if (cub->player.dirY > 0)
            return (0);
        return (1);
    }
}

void    set_line_color(t_cub *cub, t_dist *dist, float wallX)
{
    int     h;
    int     color;
	
    color = WALLCOLORX;
    // color = 0xDBACD4;
    // if (dist->wallSideX == 1)
    //     color /= 1.0005;
	h = -1;
	color = cub->img.colors[1];

	while (++h < screenH)
	{
		if (h >= cub->render_img.floorPoint && h < cub->render_img.ceilingPoint)
		{
			color = get_color_img(&cub->img.wall[get_index(cub, dist)], 
			        wallX, calculate_y(&cub->render_img, h));
            if (dist->wallSideX)
                color = 0xFF00FF;
            // color = 0xDBACD4;
            // if (dist->wallSideX == 1)
            //     color /= 0.005;
    	    if (cub->player.obj_hit == '2')
			    color = DOORCOLOR;
        }
		else if (h >= cub->render_img.ceilingPoint)
			color = cub->img.colors[0];
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, color);
	}
}

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
    cub->render_img.wallHeight = (int)(screenH /  dist->fisheyeDist) / 1.2;
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
        if (mtx[dist->mapX][dist->mapY] == '1' || mtx[dist->mapX][dist->mapY] == '2')
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
		get_wall_texture(cub, &dist);
        set_line_color(cub, &dist, dist.wallX * 64);

    }
    render_screen(cub);
    printf("dirx %f dirY %f\n", cub->player.dirX, cub->player.dirY);
}   
