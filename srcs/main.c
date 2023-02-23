/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/23 19:23:26 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub	*new_cube(void)
{
	static t_cub	data;

	return (&data);
}

int	close_window(t_cub *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit (0);
}

int	ft_close(int keycode, t_cub *vars)
{
	if (keycode == KEY_ESC)
		exit_free(vars, 0, "Exit Program Succesfully");
	return (0);
}

int	main(int ac, char **av)
{
	t_cub		cub;
	t_player	player;
	t_sprite	*spr;

	(void)player;
	read_file(new_cube(), av[1], ac);
	if (!read_map(new_cube()))
		exit_free(new_cube(), 1, "Wrong Map Configuration");
	check_map_elements(new_cube());
	cub = (*new_cube());
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, screenW, screenH, "cub3d");
	//test(cub);
	spr->data = alloc().calloc((sizeof(t_data)));
	put_image_to_window(spr, "../images/barril.xpm", 50, 60);
	mlx_hook(cub.win, 17, 2, close_window, &cub);
	mlx_key_hook(cub.win, ft_close, &cub);		
	mlx_loop(cub.mlx);
	return (0);
}