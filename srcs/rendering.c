/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:58:25 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/01 19:10:32 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


static void	put_crosshair(t_cub *cub)
{
	int	i;
	int	j;
	int	k;

	k = -2;
	while (++k < 2)
	{
		i = screenW / 2 - 11;
		j = -1;
		while (++j < 21)
		{
			if (i == screenW /2 - 3)
			{
				i += 6;
				j += 6;
			}
			my_mlx_pixel_put(&cub->render_img, ++i, (screenH / 2) + k, 0xFF0000);
		}
	}
	k = -2;
	while (++k < 2)
	{
		i = screenH / 2 - 11;
		j = -1;
		while (++j < 21)
		{
			if (i == screenH /2 - 3)
			{
				i += 6;
				j += 6;
			}
			my_mlx_pixel_put(&cub->render_img, (screenW / 2) + k, ++i, 0xFF0000);
		}
	}
}

static void	put_minimap(t_cub *cub)
{
	char	**mtx;
	double	i;
	double	j;
	int		x;
	int		y;
	int 	color;

	mtx = cub->map.mtx;
	i = -1;
	while (mtx[(int)++i])
	{
		j = -1;
		while (mtx[(int)i][(int)++j])
		{
			if (mtx[(int)i][(int)j] == '\n')
				break ;
			color = 0xFFFFFF;
			if (mtx[(int)i][(int)j] == '1')
				color = 0x000000;
			x = -1;
			while (++x < 28)
			{
				y = -1;
				while (++y < 28)
					my_mlx_pixel_put(&cub->render_img, j * 30 + y, i * 30 + x, color);
			}
		}
	}
	j = cub->player.posY;
	i = cub->player.posX;
	color = 0xCA12A9;
	x = -1;
	while (++x < 5)
	{
		y = -1;
		while (++y < 5)
			my_mlx_pixel_put(&cub->render_img, j * 30 + x, i * 30 + y, color);
	}
}

void	render_screen(t_cub *cub)
{
	
	put_crosshair(cub);
	put_minimap(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->render_img.ptr, 0, 0);
}