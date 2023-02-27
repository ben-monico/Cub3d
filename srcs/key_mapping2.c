/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:14:22 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/27 15:21:08 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void arrow_left_press(t_cub *cub)
{
    double  oldDirX;
    double  oldCameraPlaneX;
    double     rot;

    rot = 20;
    oldDirX = cub->player.dirX;
    oldCameraPlaneX = cub->player.fovX;
    cub->player.dirX = cub->player.dirX * cos(-rot) - cub->player.dirY * sin(-rot);
    cub->player.dirX = oldDirX * sin(-rot) + cub->player.dirY * cos(-rot);
    cub->player.fovX = cub->player.fovX * cos(-rot) - cub->player.fovY * sin(-rot);
    cub->player.fovY = oldCameraPlaneX * sin(-rot) + cub->player.fovY * cos(-rot);
    raycasting(cub);
}

void arrow_right_press(t_cub *cub)
{
    double  oldDirX;
    double  oldCameraPlaneX;
    double     rot;

    rot = 20;
    oldDirX = cub->player.dirX;
    oldCameraPlaneX = cub->player.fovX;
    cub->player.dirX = cub->player.dirX * cos(rot) - cub->player.dirY * sin(rot);
    cub->player.dirX = oldDirX * sin(rot) + cub->player.dirY * cos(rot);
    cub->player.fovX = cub->player.fovX * cos(rot) - cub->player.fovY * sin(rot);
    cub->player.fovY = oldCameraPlaneX * sin(rot) + cub->player.fovY * cos(rot);
    raycasting(cub);
}
