/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/27 11:12:39 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub	*new_cube(void)
{
	static t_cub	cub;

	return (&cub);
}

int	exit_win(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(1);
}

int	main(int ac, char **av)
{
	read_file(new_cube(), av[1], ac);
	read_map(new_cube());
	check_map_elements(new_cube());
	create_cube(new_cube());
	return (0);
}
