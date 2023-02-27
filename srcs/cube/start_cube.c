/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:15:20 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/27 17:47:05 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_cube(t_cub *cub)
{	
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, screenW, screenH, "cub3d");
    cub->line.ptr = mlx_new_image(cub->mlx, screenW, screenH);
	cub->line.addr = mlx_get_data_addr(cub->line.ptr, &cub->line.bpp,
                    &cub->line.size_line, &cub->line.endian);
	init_raycast_vars(cub);
	raycasting(cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1l << 0, press_key, cub);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->mlx);
}