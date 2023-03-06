/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:14:22 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/06 18:32:25 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void arrow_left_press(t_cub *cub)
{
    p_rotation(&cub->player, -5);
    raycasting(cub);
}

void arrow_right_press(t_cub *cub)
{
    p_rotation(&cub->player, 5);
    raycasting(cub);
}

int mouse_move(int x, int y, t_cub *cub)
{
    double  move_x;

    (void)y;
    mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
    if (x - screenW / 2 > ((int)screenW / 40) || x - screenW / 2 < -((int)screenW / 40))
	{
		move_x = MOUSE_STEP;
		if (x - screenW / 2 < 0)
			move_x = -move_x;
		p_rotation(&cub->player, move_x);
        raycasting(cub);
    
        mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
	    mlx_mouse_move(cub->mlx,cub->win, screenW / 2, screenH / 2);
	}
    return (1);
}

void p_rotation(t_player *player, double angle)
{
    double  x;
    double  y;

    angle *= 3.14159 / 180;
    x = player->dirY * cos(angle) + player->dirX * sin(angle);
    y = player->dirY * -sin(angle) + player->dirX * cos(angle);
    player->dirY = x;
    player->dirX = y;
    x = player->fovX * cos(angle) + player->fovY * sin(angle);
    y = player->fovX * -sin(angle) + player->fovY * cos(angle);  
    player->fovX = x;
    player->fovY = y;  
}

void    verify_collision_and_door(t_cub *cub, double x, double y)
{
    double  col;
    char    **mtx;

    mtx = cub->map.mtx;
    col = 0.5;
    if (mtx[(int)x][(int)cub->player.posY] != '1')
        cub->player.posX = x;
    if (mtx[(int)cub->player.posX][(int)y] != '1')
        cub->player.posY = y;
    x = -1;
    while(mtx[(int)++x])
    {
        y = -1;
        while (mtx[(int)x][(int)++y])
        {
            if (mtx[(int)x][(int)y] == '3')
                mtx[(int)x][(int)y] = '2';
        }
    }
    if (mtx[(int)(cub->player.posX)][(int)cub->player.posY] == '2')
        mtx[(int)(cub->player.posX)][(int)cub->player.posY] = '3';
    if (mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] == '2')
        mtx[(int)(cub->player.posX + col)][(int)cub->player.posY] = '3';
    if (mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] == '2')
        mtx[(int)(cub->player.posX - col)][(int)cub->player.posY] = '3';
    if (mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] == '2')
        mtx[(int)cub->player.posX][(int)(cub->player.posY + col)] = '3';
    if (mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] == '2')
        mtx[(int)cub->player.posX][(int)(cub->player.posY - col)] = '3';
}
