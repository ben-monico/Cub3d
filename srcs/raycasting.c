/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:24 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/09 17:24:11 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	get_wall_h(t_cub *cub, t_rcast *rcast)
{
	if (rcast->wallside_x == 0)
		rcast->fisheye = rcast->sidedist_x - rcast->deltadist_x;
	else
		rcast->fisheye = rcast->sidedist_y - rcast->deltadist_y;
	if (rcast->wallside_x == 0)
		rcast->wallx = cub->player.pos_y + rcast->fisheye * rcast->raydir_x;
	else
		rcast->wallx = cub->player.pos_x + rcast->fisheye * rcast->raydir_y;
	rcast->wallx -= floor((rcast->wallx));
	cub->render_img.wall_height = (int)(SCREENH / rcast->fisheye) / 1;
	cub->render_img.floorpoint = SCREENH / 2 - cub->render_img.wall_height / 2;
	cub->render_img.ceilingpoint = SCREENH / 2 \
	+ cub->render_img.wall_height / 2;
}

void	check_ray_hit(t_cub *cub, t_rcast *rcast)
{
	int		hit;
	char	**mtx;

	mtx = cub->map.mtx;
	hit = 0;
	while (hit == 0)
	{
		if (rcast->sidedist_x < rcast->sidedist_y)
		{
			rcast->sidedist_x += rcast->deltadist_x;
			rcast->map_x += rcast->step_x;
			rcast->wallside_x = 0;
		}
		else
		{
			rcast->sidedist_y += rcast->deltadist_y;
			rcast->map_y += rcast->step_y;
			rcast->wallside_x = 1;
		}
		if (mtx[rcast->map_x][rcast->map_y] == '1' \
		|| mtx[rcast->map_x][rcast->map_y] == '2' \
		|| mtx[rcast->map_x][rcast->map_y] == '3')
		{
			hit = 1;
			cub->player.obj_hit = mtx[rcast->map_x][rcast->map_y];
		}
	}
}

void	calc_sidedist(t_cub *cub, t_rcast *rcast)
{
	if (rcast->raydir_y < 0)
	{
		rcast->step_x = -1;
		rcast->sidedist_x = (cub->player.pos_x - rcast->map_x) \
		* rcast->deltadist_x;
	}
	else
	{
		rcast->step_x = 1;
		rcast->sidedist_x = (rcast->map_x + 1 - cub->player.pos_x) \
		* rcast->deltadist_x;
	}
	if (rcast->raydir_x < 0)
	{
		rcast->step_y = -1;
		rcast->sidedist_y = (cub->player.pos_y - rcast->map_y) \
		* rcast->deltadist_y;
	}
	else
	{
		rcast->step_y = 1;
		rcast->sidedist_y = (rcast->map_y + 1 - cub->player.pos_y) \
		* rcast->deltadist_y;
	}
}

void	raycasting(t_cub *cub)
{
	t_rcast	rcast;
	double	camerax;

	cub->render_img.x = -1;
	while (++cub->render_img.x < SCREENW)
	{
		camerax = 2 * cub->render_img.x / (double)SCREENW - 1;
		rcast.raydir_y = cub->player.dir_y + cub->player.fov_x * camerax;
		rcast.raydir_x = cub->player.dir_x + cub->player.fov_y * camerax;
		rcast.map_x = (int)cub->player.pos_x;
		rcast.map_y = (int)cub->player.pos_y;
		if (rcast.raydir_y == 0)
			rcast.deltadist_x = 1e30;
		else
			rcast.deltadist_x = fabs(1 / rcast.raydir_y);
		if (rcast.raydir_x == 0)
			rcast.deltadist_y = 1e30;
		else
			rcast.deltadist_y = fabs(1 / rcast.raydir_x);
		calc_sidedist(cub, &rcast);
		check_ray_hit(cub, &rcast);
		get_wall_h(cub, &rcast);
		set_line_color(cub, &rcast, rcast.wallx * cub->img.wall[0].width);
	}
	render_screen(cub);
}
