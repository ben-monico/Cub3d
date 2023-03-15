/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/03/15 18:51:32 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
