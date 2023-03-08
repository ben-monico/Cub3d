/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:58:25 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/08 22:06:23 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_squares(double j, double i, int color, int size)
{
	int	x;
	int	y;
	int	offset;

	offset = 5;
	if (color == 0xFFFFFF)
		offset = 0;
	x = -1;
	while (++x < size)
	{
		y = -1;
		while (++y < size)
			my_mlx_pixel_put(&new_cube()->render_img, j * 10 + y + \
			offset, i * 10 + x + offset, color);
	}
}

void	put_player_minmap(t_cub *cub)
{
	double	j;
	double	i;

	j = cub->player.pos_y;
	i = cub->player.pos_x;
	put_squares(j, i, 0xCA12A9, 5);
}

void	outline_minimap(char **mtx)
{
	int		i;
	int		j;

	i = -1;
	while (mtx[++i])
	{
		j = -1;
		while (mtx[i][++j] && mtx[i][j] != '\n')
		{
			if (mtx[i][j] == ' ')
				continue ;
			put_squares(j, i, 0xFFFFFF, 20);
		}
	}
}

void	put_minimap(t_cub *cub, char **mtx)
{
	int	i;
	int	j;
	int	color;

	outline_minimap(mtx);
	i = -1;
	while (mtx[++i])
	{
		j = -1;
		while (mtx[i][++j] && mtx[i][j] != '\n')
		{
			color = cub->img.colors[0];
			if (mtx[i][j] == ' ')
				continue ;
			else if (mtx[i][j] == '1')
				color = 0x414141;
			else if (mtx[i][j] == '2')
				color = 0x116611;
			else if (mtx[i][j] == '3')
				color = 0x11DD11;
			put_squares(j, i, color, 10);
		}
	}
	put_player_minmap(cub);
}

	//mlx_do_sync(cub->mlx);
void	render_screen(t_cub *cub)
{
	put_minimap(cub, cub->map.mtx);
	put_image_remove_chroma(&cub->sprites[0], \
	SCREENW - cub->sprites[0].width - 120, \
	SCREENH - cub->sprites[0].height, 0x02FFCF);
	put_image_remove_chroma(&cub->sprites[1], \
	SCREENW / 2 - 10, SCREENH / 2 - 10, 0x24FFCF);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->render_img.ptr, 0, 0);
}
