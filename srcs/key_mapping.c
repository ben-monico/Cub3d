/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:57:10 by benmonico         #+#    #+#             */
/*   Updated: 2023/02/23 23:28:40 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void w_press(t_cub *cub)
{
    (void)cub;
}

void a_press(t_cub *cub)
{
    (void)cub;
}

void s_press(t_cub *cub)
{
    (void)cub;
}

void d_press(t_cub *cub)
{
    (void)cub;
}
void a_left_press(t_cub *cub)
{
    double  oldDirX;
    double  oldCameraPlaneX;

    oldDirX = cub->player.dirX;
    oldCameraPlaneX = cub->player.fovX;
    cub->player.dirX = cub->player.dirX * cos(-90) - cub->player.dirY * sin(-90);
    cub->player.dirX = oldDirX * sin(-90) + cub->player.dirY * cos(-90);
    cub->player.fovX = cub->player.fovX * cos(-90) - cub->player.fovY * sin(-90);
    cub->player.fovY = oldCameraPlaneX * sin(-90) + cub->player.fovY * cos(-90);
    raycasting(cub);
}

void a_right_press(t_cub *cub)
{
    double  oldDirX;
    double  oldCameraPlaneX;

    oldDirX = cub->player.dirX;
    oldCameraPlaneX = cub->player.fovX;
    cub->player.dirX = cub->player.dirX * cos(90) - cub->player.dirY * sin(90);
    cub->player.dirX = oldDirX * sin(90) + cub->player.dirY * cos(90);
    cub->player.fovX = cub->player.fovX * cos(90) - cub->player.fovY * sin(90);
    cub->player.fovY = oldCameraPlaneX * sin(90) + cub->player.fovY * cos(90);
    raycasting(cub);
}