/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:26:10 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/06 19:01:55 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_cube(t_cub *cub)
{
	// t_sprite spr;
	new_cube()->mlx = mlx_init();
	load_img(cub, cub->img.path);
	new_cube()->win = mlx_new_window(new_cube()->mlx, screenW, screenH, "cub3d");
    cub->render_img.ptr = mlx_new_image(cub->mlx, screenW, screenH);
	cub->render_img.addr = mlx_get_data_addr(cub->render_img.ptr, &cub->render_img.bpp,
                    &cub->render_img.size_line, &cub->render_img.endian);
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