/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/16 18:04:55 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	exit_win(t_cub *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(1);
}

int	press_key(int key, t_cub *g)
{
	(void)g;
	if (key == KEY_ESC)
		exit_win(g);
	printf("%d\n", key);
	return (key);
}

t_cub	*start_cube(void)
{
	static t_cub data;

	return (&data);
}

int	main(int ac, char **av)
{
	char	*ext;
	t_cub	*cube;
	
	if (ac != 2)
		return (write(1, "Error\nInvalid arg count\n", 25));
	ext = string().strrchr(av[1], '.');
	if (!ext || string().strncmp(ext, ".cub", 5))
		return (write(1, "Error\nInvalid or missing map file\n", 35));
	cube = start_cube();
	
	return (0);
}
