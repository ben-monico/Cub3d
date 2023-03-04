/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:15:20 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/04 21:58:04 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <parse.h>
//render rectangles ceiling ground
void	create_cube(t_cub *cub)
{
	cub->mlx = mlx_init();
	load_img(cub, cub->img.path);
	cub->win = mlx_new_window(cub->mlx, screenW, screenH, "cub3d");
    cub->render_img.ptr = mlx_new_image(cub->mlx, screenW, screenH);
	cub->render_img.addr = mlx_get_data_addr(cub->render_img.ptr, &cub->render_img.bpp,
                    &cub->render_img.size_line, &cub->render_img.endian);
	init_raycast_vars(cub);
	raycasting(cub);
    // mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img[0], 0, 0);
    // mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img[1], 100, 100);
    // mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img[2], 200, 200);
    // mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img[3], 300, 350);
	//mlx_hook(cub->win, x_ON_MOUSEMOVE, 1L << 6, mouse_move, cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1l << 0, press_key, cub);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->mlx);
}
