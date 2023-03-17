/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:26:10 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/17 16:54:23 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_cube(t_cub *cub)
{
	cub->game_won = 0;
	cub->opening = 1;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_free(cub, 1, "Failed to init mlx.\n");
	load_img(cub, cub->img.path);
	easter_egg(cub);
	init_screens(cub);
	init_screen_images(cub);
	cub->win = mlx_new_window(cub->mlx, SCREENW, SCREENH, "cub3d");
	if (!cub->win)
		exit_free(cub, 1, "Failed to init mlx.\n");
	screen_sprite_cmp(cub);
	mlx_mouse_hide(cub->mlx, cub->win);
	init_player_vars(cub);
	raycasting(cub);
	mlx_hook(cub->win, X_ON_MOUSEMOVE, 1L << 6, mouse_move, cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1l << 0, press_key, cub);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->mlx);
}

void	load_img(t_cub *data, char **path)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->img.wall[i].ptr = mlx_xpm_file_to_image(data->mlx, \
		path[i], &data->img.wall[i].width, &data->img.wall[i].height);
		if (!data->img.wall[i].ptr)
			exit_free(data, 1, "Fail loading images.");
		data->img.wall[i].addr = mlx_get_data_addr(data->img.wall[i].ptr, \
		&data->img.wall[i].bpp, &data->img.wall[i].size_line, \
		&data->img.wall[i].endian);
	}
	data->img.wall[4].ptr = mlx_xpm_file_to_image(cube()->mlx, "img/port.xpm", \
	&data->img.wall[4].width, &data->img.wall[4].height);
	if (!data->img.wall[4].ptr)
		exit_free(data, 1, "Fail loading images");
	data->img.wall[4].addr = mlx_get_data_addr(data->img.wall[4].ptr, \
	&data->img.wall[4].bpp, &data->img.wall[4].size_line, \
	&data->img.wall[4].endian);
}

void	init_screen_images(t_cub *cub)
{
	cub->screen.ptr = mlx_new_image(cub->mlx, SCREENW, SCREENH);
	cub->screen.addr = mlx_get_data_addr(cub->screen.ptr, &cub->screen.bpp, \
		&cub->screen.size_line, &cub->screen.endian);
	cub->sprites[0].ptr = mlx_xpm_file_to_image(cub->mlx, "img/hol.xpm", \
		&cub->sprites[0].width, &cub->sprites[0].height);
	cub->sprites[0].addr = mlx_get_data_addr(cub->sprites[0].ptr, \
		&cub->sprites[0].bpp, &cub->sprites[0].size_line, \
		&cub->sprites[0].endian);
	cub->sprites[1].ptr = mlx_xpm_file_to_image(cub->mlx, "img/crosshair.xpm", \
		&cub->sprites[1].width, &cub->sprites[1].height);
	cub->sprites[1].addr = mlx_get_data_addr(cub->sprites[1].ptr, \
		&cub->sprites[1].bpp, \
		&cub->sprites[1].size_line, &cub->sprites[1].endian);
}

void	set_player_dir_fov(t_cub *cub, char **mtx, int x, int y)
{
	cub->player.fov_x = 0;
	cub->player.fov_y = 0;
	cub->player.dir_y = 0;
	cub->player.dir_x = 0;
	if (mtx[x][y] == 'E')
	{
		cub->player.dir_x = 1;
		cub->player.fov_x = 0.66;
	}
	else if (mtx[x][y] == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.fov_x = -0.66;
	}
	else if (mtx[x][y] == 'S')
	{
		cub->player.dir_y = 1;
		cub->player.fov_y = -0.66;
	}
	else if (mtx[x][y] == 'N')
	{
		cub->player.dir_y = -1;
		cub->player.fov_y = 0.66;
	}
	mtx[x][y] = '0';
}

void	init_player_vars(t_cub *cub)
{
	char	**mtx;
	int		x;
	int		y;

	mtx = cub->map.mtx;
	x = -1;
	while (mtx[++x])
	{
		y = -1;
		while (mtx[x][++y])
		{
			if (mtx[x][y] == 'N' || mtx[x][y] == 'S'
			|| mtx[x][y] == 'E' || mtx[x][y] == 'W')
			{
				cub->player.pos_x = x + 0.5;
				cub->player.pos_y = y + 0.5;
				set_player_dir_fov(cub, mtx, x, y);
				return ;
			}
		}
	}
}
