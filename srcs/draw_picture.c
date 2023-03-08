/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_picture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:19:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/08 22:24:04 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	calculate_y(t_data *line, float i);

int	set_aux(t_cub *cub, t_dist *dist, float wallx, double y)
{
	int	color;

	if (dist->wallside_x)
		color = get_color_img(&cub->img.wall[!(dist->raydir_x > 0) + 2], \
	wallx, y);
	else
		color = get_color_img(&cub->img.wall[!(dist->raydir_y > 0)], \
		wallx, y);
	if (cub->player.obj_hit == '2' || cub->player.obj_hit == '3')
		color = (color >> 8) & 0xFF20;
	else if (dist->wallside_x == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

int	get_portal_color(t_cub *cub, float wallx, double y, int h)
{
	int	c;

	c = get_color_img(&cub->sprites[2], wallx, y);
	if (c > 0x010101)
	{
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, c);
		return (0);
	}
	return (c);
}

void	set_line_color(t_cub *cub, t_dist *dist, float wallx)
{
	int		h;
	int		c;
	double	y;

	h = -1;
	c = cub->img.colors[1];
	while (++h < SCREENH)
	{
		if (h >= cub->render_img.floorpoint && h < cub->render_img.ceilingpoint)
		{
			y = calculate_y(&cub->render_img, h);
			if (cub->player.obj_hit == '3')
			{
				if (!get_portal_color(cub, wallx, y, h))
					continue ;
				c = get_portal_color(cub, wallx, y, h);
			}
			c = set_aux(cub, dist, wallx, y);
		}
		else if (h >= cub->render_img.ceilingpoint)
			c = cub->img.colors[0];
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, h, c);
	}
}

double	calculate_y(t_data *line, float i)
{
	static double	y;
	static double	step_y;
	static int		oldcamx;

	if (line->ceilingpoint - line->floorpoint > SCREENH)
		return ((float)(i - line->floorpoint) / (line->ceilingpoint - \
		line->floorpoint) * new_cube()->img.wall[0].height);
	if (step_y == 0 || oldcamx != line->x)
	{
		oldcamx = line->x;
		step_y = (float)(i - line->floorpoint) / (line->ceilingpoint - \
		line->floorpoint) * new_cube()->img.wall[0].height;
		y = 0;
		return (y);
	}
	y += step_y;
	if (y > new_cube()->img.wall[0].height)
		y = new_cube()->img.wall[0].height;
	return (y);
}
