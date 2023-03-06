/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/06 16:51:37 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	load_img(t_cub *data, char **path)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->img.wall[i].ptr = mlx_xpm_file_to_image(data->mlx, \
		path[i], &data->img.wall[i].width, &data->img.wall[i].height);
		data->img.wall[i].addr = mlx_get_data_addr(data->img.wall[i].ptr, &data->img.wall[i].bpp, \
		&data->img.wall[i].size_line, &data->img.wall[i].endian);
		if (!data->img.wall[i].ptr)
		{
			clean_parsing(parsing());
			exit_free(data, 1, "Fail loading images");
		}
	}
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
