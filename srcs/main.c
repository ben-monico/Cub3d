/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/17 01:12:24 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_map	tester_map()
{
	t_map mtx;

	mtx.mtx = alloc().calloc(sizeof(char *) * 6);
	mtx.mtx[0] = string().strdup("11111111111111");
	mtx.mtx[1] = string().strdup("1000000000000001");
	mtx.mtx[2] = string().strdup("1000000N00000001");
	mtx.mtx[3] = string().strdup("1000000000001111");
	mtx.mtx[4] = string().strdup("11111111111111111");
	mtx.mtx[5] = NULL;
	
	mtx.p_orientation = 'N';
	mtx.f_c = alloc().calloc(sizeof(int) * 4);
	mtx.f_c[0] = 220;
	mtx.f_c[2] = 100;
	mtx.f_c[3] = 0;
	mtx.c_c = alloc().calloc(sizeof(int) * 4);
	mtx.c_c[0] = 225;
	mtx.c_c[2] = 30;
	mtx.c_c[3] = 0;
	return(mtx);
}

t_cub	*new_cube(void)
{
	static	t_cub	data;

	return(&data);
}
//int	exit_win(t_cub *cube)
//{
//	mlx_destroy_window(cube->mtx, cube->win);
//	exit(1);
//}

int	press_key(int key, t_cub *g)
{
	(void)g;
	//if (key == KEY_ESC)
		//exit_win(g);
	printf("%d\n", key);
	printf("esc %d\n", KEY_ESC);
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
	// char	*ext;

	(void)cub;
	(void)av;
	(void)ac;

	if (!(read_file(new_cube(), av[1])))
		exit_free(new_cube(), 1, "File Corrupted");
	int	i = -1;
	while (new_cube()->map.mtx && new_cube()->map.mtx[++i])
		printf("%s\n", new_cube()->map.mtx[i]);
	//printf("p_orient: %c\n", mtx.p_orientation);
	//printf("F: %d, %d, %d\n", mtx.f_c[0], mtx.f_c[1], mtx.f_c[2]);
	//printf("C: %d, %d, %d\n", mtx.c_c[0], mtx.c_c[1], mtx.c_c[2]);
	// if (ac != 2)
	// {
	// 	write(1, "Error\nInvalid arg count\n", 25);
	// 	return (1);
	// }
	// ext = string().strrchr(av[1], '.');
	// if (!ext || string().strncmp(ext, ".cub", 5))
	// {
	// 	write(1, "Error\nInvalid or missing mtx file\n", 35);
	// 	return (1);
	// }
	//g.mtx = mlx_init();
	//g.win = mlx_new_window(g.mtx, 800, 600, "cub3d");
	//testing images
	//t_img pink_sqr;
	//pink_sqr.ptr = mlx_new_image(g.mtx, 250, 250);
	//pink_sqr.addr = mlx_get_data_addr(pink_sqr.ptr, &pink_sqr.bpp, &pink_sqr.size_line, &pink_sqr.endian);
	//int h,w;
	//h = 0;
	//while (h < 200)
	//{
	//	w = 0;
	//	while (w < 200)
	//	{
	//		my_mlx_pixel_put(&pink_sqr, w+10, h+10, 0xFFFFFF);
	//		w++;
	//	}
	//	h++;
	//}
	// my_mlx_pixel_put(&pink_sqr, 5, 5, 0xFFFFFF);
	//mlx_put_image_to_window(g.mtx, g.win, pink_sqr.ptr, 0, 0); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cube. Try changing its values to check different coordinates.
	//end of image testing
	//mlx_hook(g.win, X_EVENT_KEY_PRESS, 0, press_key, &g);
	//mlx_hook(g.win, X_EVENT_KEY_EXIT, 0, exit_win, &g);
	//mlx_loop(g.mtx);
	exit_free(new_cube(), 0, "Exit Successfully");
	return (0);
}