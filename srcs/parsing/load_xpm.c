/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/03 18:36:59 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

/* void	load_img(t_cub *data, char **path)
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
		printf("%")
		data->img.img[i] = mlx_xpm_file_to_image(data->win, \
		path[i], &width, &height);
		printf("%p\n", data->img.img[i]);
		if (!data->img.img[i])
		{
			clean_parsing(parsing());
			exit_free(data, 1, "Fail loading images");		
		}
	}
} */

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
