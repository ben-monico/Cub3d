/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/17 23:45:38 by mgranate_ls      ###   ########.fr       */
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
		data->img.img[i] = mlx_xpm_file_to_image(data->win, \
		path[i], &width, &height);
		if (!data->img.img[i])
		{
			clean_parsing(parsing());
			exit_free(data, 1, "Fail loading images");		
		}
	}
}