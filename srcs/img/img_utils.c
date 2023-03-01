/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:58:29 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/01 11:51:23 by bcarreir         ###   ########.fr       */
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
	char			*dst;
	unsigned int	color;
	
	//printf("data->add: %p\n", data->addr);
	dst = data->addr + (y * data->size_line + x	* (data->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	put_image_to_window(t_sprite *spr, char *file, int x, int y)
{
	static t_data	img;
	int				h;
	int				w;
	
	(void)x;
	(void)y;
	img = spr->data;
	img.ptr = mlx_xpm_file_to_image(new_cube()->mlx, file, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
	&img.size_line, &img.endian);
	h = -1;
	while (++h < img.height)
	{
		w = -1;
		while (++w < img.width)
		{
	 		my_mlx_pixel_put(&new_cube()->render_img, h, w, \
			get_color_img(&img, h, w));
		}
	}
	printf("h %d w %d\n", h,w );
}