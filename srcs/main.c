/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/12 19:34:00 by mgranate_ls      ###   ########.fr       */
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

void	screen_sprite_cmp(t_cub *cub, char **mtx)
{
	int	x;
	int	y;

	y = -1;
	x = -1;
	while (mtx[y + 1][++x])
		;
	while (mtx[++y])
		;
	if (y * 10 + 10 >= SCREENH || x * 10 + 10 >= SCREENW)
		exit_free(cub, 1, "Screen dimensions too small for minimap.\n");
	x = -1;
	while (cub->sprites[++x].ptr)
		if (cub->sprites[x].width >= SCREENW || \
		cub->sprites[x].height >= SCREENH)
			exit_free(cub, 1, "Screen dimensions too small.\n");
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

t_cub	*cube(void)
{
	static t_cub	cub;

	return (&cub);
}

int	main(int ac, char **av)
{
	read_file(cube(), av[1], ac);
	read_map(cube());
	check_map_elements(cube());
	create_cube(cube());
	return (0);
}
