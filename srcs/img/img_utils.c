/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:58:29 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 22:48:57 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int*)dst = color;
}

int	get_color_img(t_data *data, int x, int y)
{
	char		*dst;
	int			color;
	
	//printf("data->add: %p\n", data->addr);
	dst = data->addr + (y * data->size_line + x \
	* (data->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	put_image_to_window(t_sprite *spr, char *file, int x, int y)
{
	static t_data	img;
	int				h;
	int				w;
	
	img = spr->data;
	//img = img;
	img.ptr = mlx_xpm_file_to_image(new_cube()->mlx, file, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
	&img.size_line, &img.endian);
	h = -1;
	while (++h < img.height)
	{
		w = -1;
		while (++w < img.width)
		{
	 		my_mlx_pixel_put(&img, w + x, h + y, \
			get_color_img(&img, h, w));
		}
	}
}