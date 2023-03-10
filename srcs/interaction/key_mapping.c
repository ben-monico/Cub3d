/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:57:10 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/10 00:41:09 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	press_key(int key, t_cub *cub)
{
	if (cub->game_won && key != KEY_ESC)
		return (1);
	if (key == KEY_ESC)
		exit_free(cub, 0, "Exit Program Succesfully");
	else if (key == KEY_W)
		w_press(cub);
	else if (key == KEY_A)
		a_press(cub);
	else if (key == KEY_S)
		s_press(cub);
	else if (key == KEY_D)
		d_press(cub);
	else if (key == ARROW_RIGHT)
		arrow_right_press(cub);
	else if (key == ARROW_LEFT)
		arrow_left_press(cub);
	else if (key == KEY_SPACE)
		open_portal(cub);
	else
		return (1);
	if (!cub->game_won)
		raycasting(cub);
	return (0);
}

void	w_press(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.pos_x + cub->player.dir_y * DUB_STEP;
	y = cub->player.pos_y + cub->player.dir_x * DUB_STEP;
	verify_collision_and_door(x, y);
}

void	a_press(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.pos_x - cub->player.fov_x * DUB_STEP;
	y = cub->player.pos_y - cub->player.fov_y * DUB_STEP;
	verify_collision_and_door(x, y);
}

void	s_press(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.pos_x - cub->player.dir_y * DUB_STEP;
	y = cub->player.pos_y - cub->player.dir_x * DUB_STEP;
	verify_collision_and_door(x, y);
}

void	d_press(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.pos_x + cub->player.fov_x * DUB_STEP;
	y = cub->player.pos_y + cub->player.fov_y * DUB_STEP;
	verify_collision_and_door(x, y);
}
