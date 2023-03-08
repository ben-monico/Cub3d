/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/08 22:24:04 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	get_wall_h(t_cub *cub, t_dist *dist)
{
	if (dist->wallside_x == 0)
		dist->fisheye = dist->sidedist_x - dist->deltadist_x;
	else
		dist->fisheye = dist->sidedist_y - dist->deltadist_y;
	if (dist->wallside_x == 0)
		dist->wallx = cub->player.pos_y + dist->fisheye * dist->raydir_x;
	else
		dist->wallx = cub->player.pos_x + dist->fisheye * dist->raydir_y;
	dist->wallx -= floor((dist->wallx));
	cub->render_img.wall_height = (int)(SCREENH / dist->fisheye) / 1;
	cub->render_img.floorpoint = SCREENH / 2 - cub->render_img.wall_height / 2;
	cub->render_img.ceilingpoint = SCREENH / 2 \
	+ cub->render_img.wall_height / 2;
}

void	check_ray_hit(t_cub *cub, t_dist *dist)
{
	int		hit;
	char	**mtx;

	mtx = cub->map.mtx;
	hit = 0;
	while (hit == 0)
	{
		if (dist->sidedist_x < dist->sidedist_y)
		{
			dist->sidedist_x += dist->deltadist_x;
			dist->map_x += dist->step_x;
			dist->wallside_x = 0;
		}
		else
		{
			dist->sidedist_y += dist->deltadist_y;
			dist->map_y += dist->step_y;
			dist->wallside_x = 1;
		}
		if (mtx[dist->map_x][dist->map_y] == '1' \
		|| mtx[dist->map_x][dist->map_y] == '2' \
		|| mtx[dist->map_x][dist->map_y] == '3')
		{
			hit = 1;
			cub->player.obj_hit = mtx[dist->map_x][dist->map_y];
		}
	}
}

void	calc_sidedist(t_cub *cub, t_dist *dist)
{
	if (dist->raydir_y < 0)
	{
		dist->step_x = -1;
		dist->sidedist_x = (cub->player.pos_x - dist->map_x) \
		* dist->deltadist_x;
	}
	else
	{
		dist->step_x = 1;
		dist->sidedist_x = (dist->map_x + 1 - cub->player.pos_x) \
		* dist->deltadist_x;
	}
	if (dist->raydir_x < 0)
	{
		dist->step_y = -1;
		dist->sidedist_y = (cub->player.pos_y - dist->map_y) \
		* dist->deltadist_y;
	}
	else
	{
		dist->step_y = 1;
		dist->sidedist_y = (dist->map_y + 1 - cub->player.pos_y) \
		* dist->deltadist_y;
	}
}

void	raycasting(t_cub *cub)
{
	t_dist	dist;
	double	camerax;

	cub->render_img.x = -1;
	while (++cub->render_img.x < SCREENW)
	{
		camerax = 2 * cub->render_img.x / (double)SCREENW - 1;
		dist.raydir_y = cub->player.dir_y + cub->player.fov_x * camerax;
		dist.raydir_x = cub->player.dir_x + cub->player.fov_y * camerax;
		dist.map_x = (int)cub->player.pos_x;
		dist.map_y = (int)cub->player.pos_y;
		if (dist.raydir_y == 0)
			dist.deltadist_x = 1e30;
		else
			dist.deltadist_x = fabs(1 / dist.raydir_y);
		if (dist.raydir_x == 0)
			dist.deltadist_y = 1e30;
		else
			dist.deltadist_y = fabs(1 / dist.raydir_x);
		calc_sidedist(cub, &dist);
		check_ray_hit(cub, &dist);
		get_wall_h(cub, &dist);
		set_line_color(cub, &dist, dist.wallx * cub->img.wall[0].width);
	}
	render_screen(cub);
}
