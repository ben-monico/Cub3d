/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:37:53 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/15 18:40:13 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_screens(t_cub *cub)
{
	cub->img.wall[6].ptr = mlx_xpm_file_to_image(cube()->mlx, "img/win.xpm", \
	&cub->img.wall[6].width, &cub->img.wall[6].height);
	cub->img.wall[6].addr = mlx_get_data_addr(cub->img.wall[6].ptr, \
	&cub->img.wall[6].bpp, &cub->img.wall[6].size_line, \
	&cub->img.wall[6].endian);
	cub->img.wall[7].ptr = mlx_xpm_file_to_image(cube()->mlx, "img/open.xpm", \
	&cub->img.wall[7].width, &cub->img.wall[7].height);
	cub->img.wall[7].addr = mlx_get_data_addr(cub->img.wall[7].ptr, \
	&cub->img.wall[7].bpp, &cub->img.wall[7].size_line, \
	&cub->img.wall[7].endian);
}

void	screen_sprite_cmp(t_cub *cub)
{
	int	x;

	if (MINIMAP_H >= SCREENH || MINIMAP_W >= SCREENW)
		exit_free(cub, 1, "Screen dimensions too small for minimap.\n");
	x = 0;
	while (x < 2 && cub->sprites[x].ptr)
	{
		if (cub->sprites[x].width >= SCREENW || \
		cub->sprites[x].height >= SCREENH)
			exit_free(cub, 1, "Screen dimensions too small.\n");
		x++;
	}
}

void	ft_screens(int i)
{
	t_cub	*cub;
	int		h;
	int		w;
	int		color;

	cub = cube();
	if (i == 6)
		cub->game_won = 1;
	h = -1;
	w = -1;
	if (cub->img.wall[i].width != SCREENW || \
	cub->img.wall[i].height != SCREENH)
		return ;
	while (++w < cub->img.wall[i].width)
	{
		h = -1;
		while (++h < cub->img.wall[i].height)
		{
			color = get_color_img(&cub->img.wall[i], w, h);
			my_mlx_pixel_put(&cub->screen, w, h, color);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
}
