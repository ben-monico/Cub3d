/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:58:29 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/10 16:52:56 by bcarreir         ###   ########.fr       */
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

int	calc_prs(int dir, int color)
{
	static int	prsh;
	static int	prsw;
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
		if (prsh == 15 || prsh == -15)
			y *= -1;
		prsh += y;
		return (prsh);
	}
	if (prsw == 30 || prsw == -30)
		x *= -1;
	prsw += x;
	return (prsw);
}

void	put_image_remove_chroma(t_data *img, int offsetW, \
			int offsetH, int chroma_max)
{
	int	h;
	int	w;
	int	color;
	int	prsh;
	int	prsw;

	prsw = calc_prs(0, chroma_max);
	prsh = calc_prs(1, chroma_max);
	w = -1;
	while (++w < img->width)
	{
		h = -1;
		while (++h < img->height)
		{
			color = get_color_img(img, w, h);
			if ((color >= 0x000300 && color <= chroma_max) \
			|| offsetH + h + prsh + 30 > SCREENH)
				continue ;
			my_mlx_pixel_put(&cube()->screen, offsetW + w + prsw, \
			offsetH + h + prsh + 30, color);
		}
	}
}
