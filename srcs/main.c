/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/24 00:28:21 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub	*new_cube(void)
{
	static t_cub	data;

	return (&data);
}

int	main(int ac, char **av)
{
	read_file(new_cube(), av[1], ac);
	read_map(new_cube());
	check_map_elements(new_cube());
	create_cube(new_cube());
	return (0);
}
