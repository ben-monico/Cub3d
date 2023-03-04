/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:42:25 by mgranate          #+#    #+#             */
/*   Updated: 2023/03/04 22:50:31 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	get_wall_texture(t_cub *data, t_dist *dst)
{
	double	wall;
	// printf("fisheye: %lf\n",dst->fisheyeDist);
	// printf("rayfirY: %lf\n",dst->raydirY);
	// printf("posY: %lf\n",data->player.posY);
	// printf("wallside: %d\n",dst->wallSideY);
	if (dst->wallSideY == 0)
		wall = data->player.posY + dst->fisheyeDist * dst->raydirY;
	else
		wall = data->player.posX + dst->fisheyeDist * dst->raydirX;
	wall -= floor((wall));
	return (wall);
}

void	get_textures(t_cub *cub, int start, int end)
{
	int 		res;
	static	int a;
	static	t_data img;

	if (!a)
	{
		a = 1;
		img.ptr = mlx_xpm_file_to_image(cub->mlx, cub->img.path[1], &img.width, &img.height);
		img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
		&img.size_line, &img.endian);
		
	}
	res = end - start;
	printf("%d\n", res);
	if (cub->render_img.x > img.width)
		return ;
	while (++start < end)
	{
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, start, get_color_img(&img, start, cub->render_img.x));
	}
}