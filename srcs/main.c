/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/18 00:02:07 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_map	tester_map(void)
{
	t_map	mtx;

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
	static t_cub	data;

	return (&data);
}

int	exit_win(t_cub *cube)
{
	mlx_destroy_window(cube->mlx, cube->win);
	exit(1);
}

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

	if (ac != 2)
	{
		write(1, "Error\nInvalid arg count\n", 25);
		return (1);
	}
	if (!(read_file(new_cube(), av[1])))
		exit_free(new_cube(), 1, "File Corrupted");
	int	i = -1;
	while (new_cube()->map.mtx && new_cube()->map.mtx[++i])
		printf("%s", new_cube()->map.mtx[i]);
	i = -1;
	while (new_cube()->img.img[++i])
		printf("%s\n", (char *)new_cube()->img.img[i]);
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, 800, 600, "cub3d");
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 0, press_key, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_EXIT, 0, exit_win, &cub);
	mlx_loop(cub.mlx);
	exit_free(new_cube(), 0, "Exit Successfully");
	return (0);
}