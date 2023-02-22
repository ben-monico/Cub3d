/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/22 15:15:31 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub	*new_cube(void)
{
	static t_cub	data;
	if (!data.mlx)
	{
		data.map_mtx = alloc().calloc(sizeof(int **));
	}

	return (&data);
}

int	exit_win(t_cub *cube)
{
	mlx_destroy_window(cube->mlx, cube->win);
	exit(1);
}

int	press_key(int key, t_cub *cub)
{
	(void)cub;
	if (key == KEY_ESC)
		exit_win(cub);
	printf("%d\n", key);
	return (key);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	t_cub		cube;
	t_player	player;

	(void)player;
	if (ac != 2)
	{
		write(1, "Error\nInvalid arg count\n", 25);
		return (1);
	}
	read_file(new_cube(), av[1]);
	if (!read_map(new_cube()))
		exit_free(new_cube(), 1, "Wrong Map Configuration");
	check_map_elements(new_cube());
	cube = (*new_cube());
	int	i = -1;
	while (cube.map.mtx[++i])
		printf("%s", cube.map.mtx[i]);
	printf("\n");
	printf("img.F_C: %d\n", cube.img.colors[0]);
	printf("img.C_C: %d\n", cube.img.colors[1]);
	printf("Nbr Player: %d\n", cube.map.num_player);
	printf("Nbr Player_x: %d\n", cube.map.player_x);
	printf("Nbr Player_y: %d\n", cube.map.player_y);
	printf("Player Orientation: %c\n", cube.map.p_orientation);
	cube.mlx = mlx_init();
	cube.win = mlx_new_window(cube.mlx, screenW, screenH, "cub3d");
	
	// testing images
	
	// t_img pink_sqr;
	// pink_sqr.ptr = mlx_new_image(cube.mlx, 1, 250);
	// pink_sqr.addr = mlx_get_data_addr(pink_sqr.ptr, &pink_sqr.bpp, &pink_sqr.size_line, &pink_sqr.endian);
	// int h,w;
	// h = 0;
	// while (h < 250)
	// {
	// 	w = 0;
	// 	while (w < 1)
	// 	{
	// 		my_mlx_pixel_put(&pink_sqr, w, h, abs(cube.img.colors[1]));
	// 		// printf("h = %d\n", h);
	// 		w++;
	// 	}
	// 	h++;
	// }
	// mlx_put_image_to_window(cube.mlx, cube.win, pink_sqr.ptr, 10, 100); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cube. Try changing its values to check different coordinates.
	
	// end of image testing
	
	raycasting(&cube, &player);
	mlx_hook(cube.win, X_EVENT_KEY_PRESS, 0, press_key, &cube);
	mlx_hook(cube.win, X_EVENT_KEY_EXIT, 0, exit_win, &cube);
	mlx_loop(cube.mlx);
	// exit_free(new_cube(), 1, "Exit Program Successfully");
	return (0);
}