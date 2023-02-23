/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:58:29 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 19:22:40 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <img.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int*)dst = color;
}

int	get_color_img(t_data data, int x, int y)
{
	char		*dst;
	int			color;

	dst = data.addr + (y * data.size_line + x \
	* (data.bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	put_image_to_window(t_sprite *spr, char *file, int x, int y)
{
	t_data	img;
	int		h;
	int		w;
	
	img = spr->data;
	(void)img;
	printf("%s\n", file);
	img.ptr = mlx_xpm_file_to_image(new_cube()->mlx, "barril.xpm", &img.width, &img.height);
	//mlx_put_image_to_window(new_cube()->mlx, new_cube()->win, img.ptr,
	//		x, y);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
	&img.size_line, &img.endian);
	printf("%d\n", img.width);
	printf("%d\n", img.height);
	h = -1;
	while (++h < img.height)
	{
		w = -1;
		while (++w < img.width)
		{
	 		my_mlx_pixel_put(&img, w + x, h + y, \
			get_color_img(img, h, w));
		}
	}
}