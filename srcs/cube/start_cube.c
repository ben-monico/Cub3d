/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:15:20 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/06 16:11:40 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <parse.h>
//render rectangles ceiling ground
void	create_cube(t_cub *cub)
{
	// t_sprite spr;
	new_cube()->mlx = mlx_init();
	new_cube()->win = mlx_new_window(new_cube()->mlx, screenW, screenH, "cub3d");
    cub->render_img.ptr = mlx_new_image(cub->mlx, screenW, screenH);
	cub->render_img.addr = mlx_get_data_addr(cub->render_img.ptr, &cub->render_img.bpp,
                    &cub->render_img.size_line, &cub->render_img.endian);
    mlx_mouse_hide(cub->mlx, cub->win);
	init_raycast_vars(cub);
	raycasting(cub);
	mlx_hook(cub->win, x_ON_MOUSEMOVE, 1L << 6, &mouse_move, cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1l << 0, press_key, cub);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->mlx);
}
