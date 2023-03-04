/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/04 22:12:19 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	load_img(t_cub *data, char **path)
{
	int	i;
	int	width;
	int	height;
	
	data->img.img = alloc().calloc((sizeof(void *) * 5));
	if (!data->img.img)
	{
		clean_parsing(parsing());
		exit_free(data, 1, "Allocation for Img Failed");
	}
	width = SIZE_X;
	height = SIZE_Y;
	i = -1;
	while (++i < 4)
	{
		data->img.img[i] = mlx_xpm_file_to_image(data->mlx, \
		path[i], &width, &height);
		if (!data->img.img[i])
		{
			clean_parsing(parsing());
			exit_free(data, 1, "Fail loading images");
		}
	}
	data->img.no_text = alloc().calloc((sizeof(t_data)));
	data->img.so_text = alloc().calloc((sizeof(t_data)));
	data->img.ea_text = alloc().calloc((sizeof(t_data)));
	data->img.we_text = alloc().calloc((sizeof(t_data)));
	data->img.no_text->addr = mlx_get_data_addr(data->img.img[0], &data->img.no_text->bpp,
			&data->img.no_text->size_line, &data->img.no_text->endian);
	// data->img.so_text.addrs = mlx_get_data_addr(data->img.img[1], &data->img->so_text.bits_per_pixel,
	// 		&data->img->so_text.line_length, &data->img->so_text.endian);
	// data->img.ea_text.addrs = mlx_get_data_addr(data->img.img[2], &data->img->ea_text.bits_per_pixel,
	// 		&data->img->ea_text.line_length, &data->img->ea_text.endian);
	// data->img.we_text.addrs = mlx_get_data_addr(data->img.img[3], &data->img->we_text.bits_per_pixel,
	// 		&data->img->we_text.line_length, &data->img->we_text.endian);
}

int	get_colors(char *clr, t_parse *parse)
{
	int	i;
	int	rgb[3];
	
	i = 0;
	rgb[i] = string().atoi(clr);
	if (rgb[0] > 255 || rgb[0] < 0)
	{
		clean_parsing(parse);
		exit_free(new_cube(), 1, "Not a recognizable RGB range system");
	}
	while (++i < 3)
	{
		while (string().isdig(*clr))
			clr++;
		if (*clr != ',')
		{
			clean_parsing(parse);
			exit_free(new_cube(), 1, "Not a recognizable RGB range system");	
		}
		clr++;
		rgb[i] = string().atoi(clr);
		if (rgb[i] > 255 || rgb[i] < 0)
		{
			clean_parsing(parse);
			exit_free(new_cube(), 1, "Not a recognizable RGB range system");
		}
	}
	i = 255;
	return (i << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
