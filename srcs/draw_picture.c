/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_picture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:19:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/07 23:27:24 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	calculate_y(t_data *line, float i);

void    set_line_color(t_cub *cub, t_dist *dist, float wallX)
{
    int     h;
    int     color;
    double  y;
	
	h = -1;
	color = cub->img.colors[1];
	while (++h < screenH)
	{
		if (h >= cub->render_img.floorPoint && h < cub->render_img.ceilingPoint)
		{
            y = calculate_y(&cub->render_img, h);
                if (cub->player.obj_hit == '3')
                {   
                    color = get_color_img(&cub->sprites[2],
				    wallX, y);
                    if (color > 0x18B001)
                    {
                        my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, color);
                        continue ;
                    }
                }
                if (dist->wallSideX)
			    color = get_color_img(&cub->img.wall[!(dist->raydirX > 0) + 2],
			    	wallX, y);
			    else
			    	color = get_color_img(&cub->img.wall[!(dist->raydirY > 0)],
			    		wallX, y);
            
            if (cub->player.obj_hit == '2')
                color = (color >> 1) & 0x27FF27;
            else if(dist->wallSideX == 1)
                color = (color >> 1) & 8355711;

        }
		else if (h >= cub->render_img.ceilingPoint)
			color = cub->img.colors[0];
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, color);
	}
}

double	calculate_y(t_data *line, float i)
{
    static double   y;
    static int      oldcamX;
    static double   stepY;
    // return ((float)(i - line->floorPoint) /	(line->ceilingPoint - line->floorPoint) * TEX_SIZE);
    if (line->ceilingPoint - line->floorPoint > screenH)
        return ((float)(i - line->floorPoint) /	(line->ceilingPoint - line->floorPoint) * TEX_SIZE);
    if (stepY == 0 || oldcamX != line->x)
    {
        oldcamX = line->x;
        stepY = (float)(i - line->floorPoint) /	(line->ceilingPoint - line->floorPoint) * TEX_SIZE;
        y = 0;
        return (y);
    }
    y += stepY;
    if (y > TEX_SIZE)
        y = TEX_SIZE;
    return (y);
}