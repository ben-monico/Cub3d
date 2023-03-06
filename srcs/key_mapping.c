/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:57:10 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/06 19:04:31 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int press_key(int key, t_cub *cub)
{
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
	raycasting(cub);
	return (0);
}

void w_press(t_cub *cub)
{
	double	x;
	double	y;
	
	x = cub->player.posX + cub->player.dirY * DUB_STEP;
	y = cub->player.posY + cub->player.dirX * DUB_STEP;
	verify_collision_and_door(cub, x, y);
}

void a_press(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.posX - cub->player.fovX * DUB_STEP;
	y = cub->player.posY - cub->player.fovY * DUB_STEP;
	verify_collision_and_door(cub, x, y);
}

void s_press(t_cub *cub)
{
	double	x;
	double	y;
	
	x = cub->player.posX - cub->player.dirY * DUB_STEP;
	y = cub->player.posY - cub->player.dirX * DUB_STEP;
	verify_collision_and_door(cub, x, y);
}

void d_press(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.posX + cub->player.fovX * DUB_STEP;
	y = cub->player.posY + cub->player.fovY * DUB_STEP;
	verify_collision_and_door(cub, x, y);
}
