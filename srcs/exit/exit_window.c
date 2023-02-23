/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:21:36 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 21:21:40 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_cub *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit (0);
}

int	ft_close(int keycode, t_cub *vars)
{
	if (keycode == KEY_ESC)
		exit_free(vars, 0, "Exit Program Succesfully");
	return (0);
}