/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/17 18:07:59 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_map	tester_map()
{
	t_map map;

	map.map = alloc().calloc(sizeof(char *) * 6);
	map.map[0] = string().strdup("1111111111111111");
	map.map[1] = string().strdup("1000000000000001");
	map.map[2] = string().strdup("1000000N00000001");
	map.map[3] = string().strdup("1000000000001111");
	map.map[4] = string().strdup("1111111111111111");
	map.map[5] = NULL;
	
	map.p_orientation = 'N';
	map.f_c = alloc().calloc(sizeof(int) * 4);
	map.f_c[0] = 220;
	map.f_c[2] = 100;
	map.f_c[3] = 0;
	map.c_c = alloc().calloc(sizeof(int) * 4);
	map.c_c[0] = 225;
	map.c_c[2] = 30;
	map.c_c[3] = 0;
	return(map);
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
	t_cub		cub;
	t_map		map;
	t_player	player;
	// char	*ext;

	(void)cub;
	(void)av;
	(void)ac;
	map = tester_map();
	int	i = -1;
	while (map.map[++i])
		printf("%s\n", map.map[i]);
	printf("p_orient: %c\n", map.p_orientation);
	printf("F: %d, %d, %d\n", map.f_c[0], map.f_c[1], map.f_c[2]);
	printf("C: %d, %d, %d\n", map.c_c[0], map.c_c[1], map.c_c[2]);
	// if (ac != 2)
	// {
	// 	write(1, "Error\nInvalid arg count\n", 25);
	// 	return (1);
	// }
	// ext = string().strrchr(av[1], '.');
	// if (!ext || string().strncmp(ext, ".cub", 5))
	// {
	// 	write(1, "Error\nInvalid or missing map file\n", 35);
	// 	return (1);
	// }
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, screenW, screenH, "cub3d");
	
	// testing images
	// t_img pink_sqr;
	// pink_sqr.ptr = mlx_new_image(cub.mlx, 250, 250);
	// pink_sqr.addr = mlx_get_data_addr(pink_sqr.ptr, &pink_sqr.bpp, &pink_sqr.size_line, &pink_sqr.endian);
	// int h,w;
	// h = 0;
	// while (h < 200)
	// {
	// 	w = 0;
	// 	while (w < 200)
	// 	{
	// 		my_mlx_pixel_put(&pink_sqr, w+10, h+10, 0xFFFFFF);
	// 		w++;
	// 	}
	// 	h++;
	// }
	// my_mlx_pixel_put(&pink_sqr, 5, 5, 0xFFFFFF);
	// mlx_put_image_to_window(cub.mlx, cub.win, pink_sqr.ptr, 0, 0); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cube. Try changing its values to check different coordinates.
	// end of image testing
	raycasting(&cub, &player);
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 0, press_key, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_EXIT, 0, exit_win, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
