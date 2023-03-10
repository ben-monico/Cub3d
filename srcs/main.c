/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/10 16:32:17 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	win_condition(void)
{
	t_cub	*cub;
	int		h;
	int		w;
	int		color;

	cub = cube();
	cub->game_won = 1;
	h = -1;
	w = -1;
	while (++w < cub->img.wall[6].width)
	{
		h = -1;
		while (++h < cub->img.wall[6].height)
		{
			color = get_color_img(&cub->img.wall[6], w, h);
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
