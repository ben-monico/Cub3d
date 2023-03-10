/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/10 00:41:58 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	win_condition()
{
	t_cub	*cub;
	int	h;
	int	w;
	int	color;

	cub = new_cube();
	cub->game_won = 1;
	h = -1;
	w = -1;
	while (++w < cub->img.wall[6].width)
	{
		h = -1;
		while (++h < cub->img.wall[6].height)
		{
			color = get_color_img(&cub->img.wall[6], w, h);
			my_mlx_pixel_put(&cub->render_img, w, h, color);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->render_img.ptr, 0, 0);
}

t_cub	*new_cube(void)
{
	static t_cub	cub;

	return (&cub);
}

int	main(int ac, char **av)
{
	read_file(new_cube(), av[1], ac);
	read_map(new_cube());
	check_map_elements(new_cube());
	create_cube(new_cube());
	return (0);
}
