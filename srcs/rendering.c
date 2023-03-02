/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:58:25 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/02 16:22:53 by bcarreir         ###   ########.fr       */
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
			color = cub->img.colors[1];
			if (mtx[(int)i][(int)j] == '1')
				color = 0x414141;
			x = -1;
			while (++x < 25)
			{
				y = -1;
				while (++y < 25)
					my_mlx_pixel_put(&cub->render_img, j * 25 + y, i * 25 + x, color);
			}
		}
	}
	j = cub->player.posY;
	i = cub->player.posX;
	color = 0xCA12A9;
	x = -3;
	while (++x < 3)
	{
		y = -3;
		while (++y < 3)
			my_mlx_pixel_put(&cub->render_img, j * 25 + x, i * 25 + y, color);
	}
}

void	render_screen(t_cub *cub)
{
	t_sprite spr;
	put_crosshair(cub);
	put_minimap(cub);
	// mlx_do_sync(cub->mlx);
	put_image_to_window(&spr, "images/gun.xpm", 0, 0);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->render_img.ptr, 0, 0);
}