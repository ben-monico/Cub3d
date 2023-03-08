/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_picture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:19:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/08 20:33:35 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	calculate_y(t_data *line, float i);

int	set_aux(t_cub *cub, t_dist *dist, float wallX, double y)
{
	int	color;

	if (dist->wallSideX)
		color = get_color_img(&cub->img.wall[!(dist->raydirX > 0) + 2], \
	wallX, y);
	else
		color = get_color_img(&cub->img.wall[!(dist->raydirY > 0)], \
		wallX, y);
	if (cub->player.obj_hit == '2' || cub->player.obj_hit == '3')
		color = (color >> 8) & 0xFF20;
	else if (dist->wallSideX == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

int	get_portal_color(t_cub *cub, float wallX, double y, int h)
{
	int	c;

	c = get_color_img(&cub->sprites[2], wallX, y);
	if (c > 0x010101)
	{
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, c);
		return (0);
	}
	return (c);
}

void	set_line_color(t_cub *cub, t_dist *dist, float wallX)
{
	int		h;
	int		c;
	double	y;

	h = -1;
	c = cub->img.colors[1];
	while (++h < screenH)
	{
		if (h >= cub->render_img.floorPoint && h < cub->render_img.ceilingPoint)
		{
			y = calculate_y(&cub->render_img, h);
			if (cub->player.obj_hit == '3')
			{
				if (!get_portal_color(cub, wallX, y, h))
					continue ;
				c = get_portal_color(cub, wallX, y, h);
			}
			c = set_aux(cub, dist, wallX, y);
		}
		else if (h >= cub->render_img.ceilingPoint)
			c = cub->img.colors[0];
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, c);
	}
}

double	calculate_y(t_data *line, float i)
{
	static double	y;
	static double	stepy;
	static int		oldcamx;

	if (line->ceilingPoint - line->floorPoint > screenH)
		return ((float)(i - line->floorPoint) / (line->ceilingPoint - \
		line->floorPoint) * new_cube()->img.wall[0].height);
	if (stepy == 0 || oldcamx != line->x)
	{
		oldcamx = line->x;
		stepy = (float)(i - line->floorPoint) / (line->ceilingPoint - \
		line->floorPoint) * new_cube()->img.wall[0].height;
		y = 0;
		return (y);
	}
	y += stepy;
	if (y > new_cube()->img.wall[0].height)
		y = new_cube()->img.wall[0].height;
	return (y);
}
