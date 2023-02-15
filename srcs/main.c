/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/15 17:19:29 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	exit_win(t_g *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(1);
}

int	press_key(int key, t_g *g)
{
	(void)g;
	if (key == KEY_ESC)
		exit_win(g);
	printf("%d\n", key);
	return (key);
}

int	main(int ac, char **av)
{
	t_g		g;
	char	*ext;
	
	if (ac != 2)
	{
		write(1, "Error\nInvalid arg count\n", 25);
		return (1);
	}
	ext = string().strrchr(av[1], '.');
	if (!ext || string().strncmp(ext, ".cub", 5))
	{
		write(1, "Error\nInvalid or missing map file\n", 35);
		return (1);
	}
	g.mlx = mlx_init();
	// if (!assign_xpm(&g))
	// 	return (1);
	g.win = mlx_new_window(g.mlx, 800, 600, "cub3d");
	mlx_hook(g.win, X_EVENT_KEY_PRESS, 1l << 0, press_key, &g);
	mlx_hook(g.win, X_EVENT_KEY_EXIT, 1l << 2, exit_win, &g);
	mlx_loop(g.mlx);
	return (0);
}
