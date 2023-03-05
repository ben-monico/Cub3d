/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:58:29 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/05 17:35:16 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int*)dst = color;
}

unsigned int	get_color_img(t_data *data, int x, int y)
{
	char			*dst;
	unsigned int	color;
	
	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	color = *(unsigned int*)dst;
	return (color);
}

unsigned int	get_color_wall(t_wall data, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = (data.addr + (y * data.size_line + x * (data.bpp / 8)));
	color = *(unsigned int*)dst;
	//printf("x: %d\n", x);
	//printf("y: %d\n", y);
	return (color);
}

void	put_image_to_window(t_sprite *spr, char *file, int x, int y)
{
	static t_data	img;
	static int		bobh;
	static int		bobw;
	static int		bobhdir;
	static int		bobwdir;
	static int		a;
	int				h;
	int				w;
	
	(void)x;
	(void)y;
	if (!a)
	{
		a = 1;
		img = spr->data;
		img.ptr = mlx_xpm_file_to_image(new_cube()->mlx, file, &img.width, &img.height);
		img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
		&img.size_line, &img.endian);
	}
	if (bobh == 10)
		bobhdir = 1;
	else if (bobh == -10)
		bobhdir = 0;
	if (!bobhdir)
		bobh++;
	else
		bobh--;
	if (bobw == 20)
		bobwdir = 1;
	else if (bobw == -20)
		bobwdir = 0;
	if (!bobwdir)
		bobw++;
	else
		bobw--;
	h = -1;
	while (++h < img.width)
	{
		w = -1;
		while (++w < img.height)
		{
	// 		printf("h %d w %d\n", h,w );
	// printf("w%d h%d\n", img.width, img.height);
			x = get_color_img(&img, h, w);
			// printf("color - %d\n", x);
			if (x >= 0x000000 && x <= 0x093304)
				continue ;
	 		my_mlx_pixel_put(&new_cube()->render_img, screenW - img.width - 120 + h +bobw, screenH - img.height + 30 + bobh + w, x);
		}
	}
	// printf("w%d h%d\n", img.width, img.height);
}