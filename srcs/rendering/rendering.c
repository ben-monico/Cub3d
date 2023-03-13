/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:58:25 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/13 17:07:20 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	render_screen(t_cub *cub)
{
	if (cub->opening == 1)
		ft_screens(7);
	else
	{
		new_minimap(cub, cub->map.mtx, 0.015 * 2, 0);
		put_png(&cub->sprites[0], \
		SCREENW - cub->sprites[0].width - 120, \
		SCREENH - cub->sprites[0].height, 1);
		put_png(&cub->sprites[1], \
		SCREENW / 2 - 10, SCREENH / 2 - 10, 0);
		mlx_do_sync(cub->mlx);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	}
}
