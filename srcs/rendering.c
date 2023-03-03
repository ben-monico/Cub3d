/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:58:25 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/03 20:56:43 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void	put_crosshair(t_cub *cub)
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
			if (i == screenW /2 - 5)
			{
				i += 10;
				j += 10;
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
			if (i == screenH /2 - 5)
			{
				i += 10;
				j += 10;
			}
			my_mlx_pixel_put(&cub->render_img, (screenW / 2) + k, ++i, 0xFF0000);
		}
	}
}

void	put_minimap(t_cub *cub)
{
	char	**mtx;
	double	i;
	double	j;
	int		x;
	int		y;
	int		outline;
	int 	color;

	mtx = cub->map.mtx;
	outline = 5;
	i = -1;
	color = 0xFFFFFF;
	while (mtx[(int)++i])
	{
		j = -1;
		while (mtx[(int)i][(int)++j] && mtx[(int)i][(int)j] != '\n')
		{
			if (mtx[(int)i][(int)j] == ' ')
				continue ;
			x = -1;
			while (++x < 20)
			{
				y = -1;
				while (++y < 20)
					my_mlx_pixel_put(&cub->render_img, j * 10 + y, i * 10 + x, color);
			}
		}
	}
	i = -1;
	while (mtx[(int)++i])
	{
		j = -1;
		while (mtx[(int)i][(int)++j] && mtx[(int)i][(int)j] != '\n')
		{
			if (mtx[(int)i][(int)j] == ' ')
				continue ;
			color = cub->img.colors[1];
			if (mtx[(int)i][(int)j] == '1')
				color = 0x414141;
			else if (mtx[(int)i][(int)j] == '2')
				color = DOORCOLOR;
			x = -1;
			while (++x < 10)
			{
				y = -1;
				while (++y < 10)
					my_mlx_pixel_put(&cub->render_img, j * 10 + y + outline, i * 10 + x + outline, color);
			}
			
		}
	}
	j = cub->player.posY;
	i = cub->player.posX;
	color = 0xCA12A9;
	x = -4;
	while (++x < 4)
	{
		y = -4;
		while (++y < 4)
		{
			my_mlx_pixel_put(&cub->render_img, j * 10 + x + outline, i * 10 + y + outline, color);
		}
	}
}

void	render_screen(t_cub *cub)
{
	t_sprite spr;
	put_crosshair(cub);
	put_minimap(cub);
	put_image_to_window(&spr, "images/hol.xpm", 0, 0);
	// mlx_do_sync(cub->mlx);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->render_img.ptr, 0, 0);
}