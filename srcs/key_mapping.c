/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:57:10 by benmonico         #+#    #+#             */
/*   Updated: 2023/03/01 13:46:44 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int press_key(int key, t_cub *cub)
{
	double	dubstep;

	dubstep = 0.1;
	if (key == KEY_ESC)
		exit_free(cub, 0, "Exit Program Succesfully");
	else if (key == KEY_W)
		w_press(cub, dubstep);
	else if (key == KEY_A)
		a_press(cub, dubstep);
	else if (key == KEY_S)
		s_press(cub, dubstep);
	else if (key == KEY_D)
		d_press(cub, dubstep);
	else if (key == ARROW_RIGHT)
		arrow_right_press(cub);
	else if (key == ARROW_LEFT)
		arrow_left_press(cub);
	raycasting(cub);
	return (key);
}

void w_press(t_cub *cub, double dubstep)
{
	double	x;
	double	y;
	
	x = cub->player.posX + cub->player.dirY * dubstep;
	y = cub->player.posY + cub->player.dirX * dubstep;
	if (check_collision(cub, x, y))
		return ;

	cub->player.posX = x;
	cub->player.posY = y;
}

void a_press(t_cub *cub, double dubstep)
{
	double	x;
	double	y;

	x = cub->player.posX - cub->player.fovX * dubstep;
	y = cub->player.posY - cub->player.fovY * dubstep;
    cub->player.posX = x;
	cub->player.posY = y;
}

void s_press(t_cub *cub, double dubstep)
{
	double	x;
	double	y;
	
	x = cub->player.posX - cub->player.dirY * dubstep;
	y = cub->player.posY - cub->player.dirX * dubstep;
	if (cub->map.mtx[(int)x][(int)y] && cub->map.mtx[(int)x][(int)y] == '1')
		return ;
    cub->player.posX = x;
	cub->player.posY = y;
}

void d_press(t_cub *cub, double dubstep)
{
	double	x;
	double	y;

	x = cub->player.posX + cub->player.fovX * dubstep;
	y = cub->player.posY + cub->player.fovY * dubstep;
	if (cub->map.mtx[(int)x][(int)y] && cub->map.mtx[(int)x][(int)y] == '1')
		return ;
    cub->player.posX = x;
	cub->player.posY = y;
}
