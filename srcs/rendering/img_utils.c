/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:58:29 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/10 21:23:35 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_textures(t_cub *cub, int start, int end)
{
	static int		a;
	static t_data	img;

	if (!a)
	{
		a = 1;
		img.ptr = mlx_xpm_file_to_image(cub->mlx, cub->img.path[1], \
		&img.width, &img.height);
		img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
		&img.size_line, &img.endian);
	}
	if (cub->screen.x > img.width)
		return ;
	while (++start < end)
	{
		my_mlx_pixel_put(&cub->screen, cub->screen.x, start, \
		get_color_img(&img, start, cub->screen.x));
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_img(t_data *data, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = (data->addr + (y * data->size_line + x * (data->bpp / 8)));
	color = *(unsigned int *)dst;
	return (color);
}

int	calc_bob(int dir, int color)
{
	static int	bobh;
	static int	bobw;
	static int	y;
	static int	x;

	if (color == 0x24FFCF)
		return (0);
	if (!y || !x)
	{
		y = 1;
		x = 1;
	}
	if (dir)
	{
		if (bobh == 15 || bobh == -15)
			y *= -1;
		bobh += y;
		return (bobh);
	}
	if (bobw == 30 || bobw == -30)
		x *= -1;
	bobw += x;
	return (bobw);
}

void	put_image_remove_chroma(t_data *img, int x, \
			int y, int isgun)
{
	int	h;
	int	w;
	int	color;
	int	bobh;
	int	bobw;

	bobw = calc_bob(0, isgun);
	bobh = calc_bob(1, isgun);
	w = -1;
	while (++w < img->width)
	{
		h = -1;
		while (++h < img->height)
		{
			color = get_color_img(img, w, h);
			if ((color < 0x010101) || y + h + bobh + 30 > SCREENH)
				continue ;
			my_mlx_pixel_put(&cube()->screen, x + w + bobw, \
			y + h + bobh + 30, color);
		}
	}
}
