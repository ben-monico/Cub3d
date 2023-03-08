/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:26:10 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/08 20:36:19 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_images(t_cub *cub)
{
    cub->render_img.ptr = mlx_new_image(cub->mlx, screenW, screenH);
	cub->render_img.addr = mlx_get_data_addr(cub->render_img.ptr, &cub->render_img.bpp,
                    &cub->render_img.size_line, &cub->render_img.endian);
	cub->sprites[0].ptr = mlx_xpm_file_to_image(cub->mlx, "images/hol.xpm", \
							&cub->sprites[0].width, &cub->sprites[0].height);
	cub->sprites[0].addr = mlx_get_data_addr(cub->sprites[0].ptr,
							&cub->sprites[0].bpp, &cub->sprites[0].size_line, &cub->sprites[0].endian);
	cub->sprites[1].ptr = mlx_xpm_file_to_image(cub->mlx, "images/crosshair.xpm", \
							&cub->sprites[1].width, &cub->sprites[1].height);
	cub->sprites[1].addr = mlx_get_data_addr(cub->sprites[1].ptr, &cub->sprites[1].bpp, \
		&cub->sprites[1].size_line, &cub->sprites[1].endian);
	cub->sprites[2].ptr = mlx_xpm_file_to_image(cub->mlx, "images/portal1.xpm", 
							&cub->sprites[2].width, &cub->sprites[2].height);
	cub->sprites[2].addr = mlx_get_data_addr(cub->sprites[2].ptr, &cub->sprites[2].bpp, 
		&cub->sprites[2].size_line, &cub->sprites[2].endian);
}

void	create_cube(t_cub *cub)
{
	new_cube()->mlx = mlx_init();
	load_img(cub, cub->img.path);
	get_images(cub);
	new_cube()->win = mlx_new_window(cub->mlx, screenW, screenH, "cub3d");
	init_raycast_vars(cub);
    mlx_mouse_hide(cub->mlx, cub->win);
	raycasting(cub);
	mlx_hook(cub->win, x_ON_MOUSEMOVE, 1L << 6, mouse_move, cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1l << 0, press_key, cub);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->mlx);
}

void	init_raycast_vars(t_cub *cub)
{
	char	**mtx;
	int		x;
    int		y;
	  
	mtx = cub->map.mtx;
    cub->player.fovX = 0;
    cub->player.fovY = 0;
	cub->player.dirY = 0;
	cub->player.dirX = 0;
	x = -1;
    while(mtx[++x])
    {
        y = -1;
        while (mtx[x][++y])
        {
            if (mtx[x][y] == 'N' || mtx[x][y] == 'S'
			|| mtx[x][y] == 'E' || mtx[x][y] == 'W')
            {
                cub->player.posX = x + 0.5;
                cub->player.posY = y + 0.5;
				if (mtx[x][y] == 'E')
				{
            	    cub->player.dirX = 1;
					cub->player.fovX = 0.66;
				}
				else if (mtx[x][y] == 'W')
				{
					cub->player.dirX = -1;
					cub->player.fovX = -0.66;
				}
				else if (mtx[x][y] == 'S')
				{
					 cub->player.dirY = 1;
					 cub->player.fovY = -0.66;
				}
				else if (mtx[x][y] == 'N')
				{
					cub->player.dirY = -1;
					cub->player.fovY = 0.66;
				}
				mtx[x][y] = '0';
				return ;
            }
        }
    }
}