/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:15:20 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/24 00:06:18 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	press_key(int key, t_cub *cub)
{
	printf("%d\n", key);
	(void)cub;
	if (key == KEY_W)
		w_press(cub);
	else if (key == KEY_A)
		a_press(cub);
	else if (key == KEY_S)
		s_press(cub);
	else if (key == KEY_D)
		d_press(cub);
	else if (key == ARROW_RIGHT)
		a_right_press(cub);
	else if (key == ARROW_LEFT)
		a_left_press(cub);
	else if (key == KEY_ESC)
		exit_free(cub, 0, "Exit Program Succesfully");
	return (key);
}

void	create_cube(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, screenW, screenH, "cub3d");
	init_raycast_vars(cub);
	raycasting(cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1l << 0, press_key, &cub);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->mlx);
}