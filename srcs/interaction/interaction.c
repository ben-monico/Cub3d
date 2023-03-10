/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:14:22 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/10 00:36:02 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	arrow_left_press(t_cub *cub)
{
	p_rotation(&cub->player, -5);
	raycasting(cub);
}

void	arrow_right_press(t_cub *cub)
{
	p_rotation(&cub->player, 5);
	raycasting(cub);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	double	move_x;

	if (cub->game_won)
		return (0);
	(void)y;
	mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
	if (x - SCREENW / 2 > ((int)SCREENW / 50) \
	|| x - SCREENW / 2 < -((int)SCREENW / 50))
	{
		move_x = MOUSE_STEP;
		if (x - SCREENW / 2 < 0)
			move_x = -move_x;
		p_rotation(&cub->player, move_x);
		raycasting(cub);
		mlx_mouse_move(cub->mlx, cub->win, SCREENW / 2, SCREENH / 2);
	}
	return (1);
}

void	p_rotation(t_player *player, double angle)
{
	double	x;
	double	y;

	angle *= 3.14159 / 180;
	x = player->dir_y * cos(angle) + player->dir_x * sin(angle);
	y = player->dir_y * -sin(angle) + player->dir_x * cos(angle);
	player->dir_y = x;
	player->dir_x = y;
	x = player->fov_x * cos(angle) + player->fov_y * sin(angle);
	y = player->fov_x * -sin(angle) + player->fov_y * cos(angle);
	player->fov_x = x;
	player->fov_y = y;
}

void	verify_collision_and_door(double x, double y)
{
    t_cub   *cub;
    char    **mtx;

    cub = new_cube();
    mtx = cub->map.mtx;
	if (mtx[(int)x][(int)y] == '5')
	{
		win_condition() ;
		return ;
	}
	if (mtx[(int)x][(int)y] == '3' && portal_teleport(cub, cub->map.mtx, x, y))
    	return ;
    if (mtx[(int)x][(int)cub->player.pos_y] == '0')
        cub->player.pos_x = x;
    if (mtx[(int)cub->player.pos_x][(int)y] == '0')
        cub->player.pos_y = y;
}
