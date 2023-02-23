/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:14:45 by bcarreir          #+#    #+#             */
/*   Updated: 2023/02/23 19:45:38 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub	*new_cub(void)
{
	static t_cub	data;
	if (!data.mlx)
	{
		data.map_mtx = alloc().calloc(sizeof(int **));
	}

	return (&data);
}

int	exit_win(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(1);
}

int	press_key(int key, t_cub *cub)
{
	(void)cub;
	if (key == KEY_ESC)
		exit_win(cub);
	else if (key == KEY_W)
		w_press(cub);
	else if (key == KEY_A)
		a_press(cub);
	else if (key == KEY_S)
		s_press(cub);
	else if (key == KEY_D)
		d_press(cub);
	else if (key == ARROW_LEFT)
		a_right_press(cub);
	else if (key == ARROW_LEFT)
		a_left_press(cub);
	printf("%d\n", key);
	return (key);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int*)dst = color;
}

void	init_raycast_vars(t_cub *cub)
{
	char	**mtx;
	int		x;
    int		y;
	  
	mtx = cub->map.mtx;
    cub->player.fovX = 0;
    cub->player.fovX = 0.66;
	cub->player.dirX = 0;
	cub->player.dirY = 0;
	x = -1;
    while(mtx[++x])
    {
        y = -1;
        while (mtx[x][++y])
        {
            if (mtx[x][y] == 'N' || mtx[x][y] == 'S'
			|| mtx[x][y] == 'E' || mtx[x][y] == 'W')
            {
				printf("oi\n");
                cub->player.posX = x;
                cub->player.posY = y;
				printf("x %d y %d\n", x, y);

				if (mtx[x][y] == 'N')
            	    cub->player.dirY = 1;
				else if (mtx[x][y] == 'S')
					 cub->player.dirY = -1;
				else if (mtx[x][y] == 'E')
					 cub->player.dirX = -1;
				else
					 cub->player.dirX = 1;
				return ;
            }
        }
    }
}

int	main(int ac, char **av)
{
	t_cub		cub;

	if (ac != 2)
	{
		write(1, "Error\nInvalid arg count\n", 25);
		return (1);
	}
	read_file(new_cub(), av[1]);
	if (!read_map(new_cub()))
		exit_free(new_cub(), 1, "Wrong Map Configuration");
	check_map_elements(new_cub());
	cub = (*new_cub());
	int	i = -1;
	while (cub.map.mtx[++i])
		printf("%s", cub.map.mtx[i]);
	printf("\n");
	printf("img.F_C: %d\n", cub.img.colors[0]);
	printf("img.C_C: %d\n", cub.img.colors[1]);
	printf("Nbr Player: %d\n", cub.map.num_player);
	printf("Nbr Player_x: %d\n", cub.map.player_x);
	printf("Nbr Player_y: %d\n", cub.map.player_y);
	printf("Player Orientation: %c\n", cub.map.p_orientation);
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, screenW, screenH, "cub3d");
	
	// testing images
	
	// t_img pink_sqr;
	// pink_sqr.ptr = mlx_new_image(cub.mlx, 1, 250);
	// pink_sqr.addr = mlx_get_data_addr(pink_sqr.ptr, &pink_sqr.bpp, &pink_sqr.size_line, &pink_sqr.endian);
	// int h,w;
	// h = 0;
	// while (h < 250)
	// {
	// 	w = 0;
	// 	while (w < 1)
	// 	{
	// 		my_mlx_pixel_put(&pink_sqr, w, h, abs(cub.img.colors[1]));
	// 		// printf("h = %d\n", h);
	// 		w++;
	// 	}
	// 	h++;
	// }
	// mlx_put_image_to_window(cub.mlx, cub.win, pink_sqr.ptr, 10, 100); // These zeroes are the coordinates of the window in which you want to place the first pixel of our cute pink cub. Try changing its values to check different coordinates.
	
	// end of image testing
	init_raycast_vars(&cub);
	raycasting(&cub);
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 0, press_key, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_EXIT, 0, exit_win, &cub);
	mlx_loop(cub.mlx);
	// exit_free(new_cub(), 1, "Exit Program Successfully");
	return (0);
}