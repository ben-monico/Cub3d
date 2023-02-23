/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:15:20 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 22:48:36 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_cube(t_cub *cub)
{
	t_sprite spr;

	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, screenW, screenH, "cub3d");
	put_image_to_window(&spr, "images/barril.xpm", 100, 200);
	mlx_hook(cub->win, 17, 2, close_window, cub);
	mlx_key_hook(cub->win, ft_close, cub);
	mlx_loop(cub->mlx);
}