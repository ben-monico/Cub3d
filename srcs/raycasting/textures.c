/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:42:25 by mgranate          #+#    #+#             */
/*   Updated: 2023/03/05 16:18:21 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_wall_texture(t_cub *data, t_dist *dst)
{
	/*printf("wallside: %d\n",dst->wallSideY);
	printf("posY: %lf\n",data->player.posY);
	printf("fisheye: %lf\n",dst->fisheyeDist);
	printf("rayfirY: %lf\n",dst->raydirY);*/
	if (dst->wallSideY == 0)
		dst->wallX = data->player.posY + dst->fisheyeDist * dst->raydirY;
	else
		dst->wallX = data->player.posX + dst->fisheyeDist * dst->raydirX;
	printf("wall: %lf\n", dst->wallX);
	dst->wallX -= floor((dst->wallX));
	printf("wall2: %lf\n", dst->wallX);
}

void	get_textures(t_cub *cub, int start, int end)
{
	static	int a;
	static	t_data img;

	if (!a)
	{
		a = 1;
		img.ptr = mlx_xpm_file_to_image(cub->mlx, cub->img.path[1], &img.width, &img.height);
		img.addr = mlx_get_data_addr(img.ptr, &img.bpp, \
		&img.size_line, &img.endian);
		
	}
	if (cub->render_img.x > img.width)
		return ;
	while (++start < end)
	{
		my_mlx_pixel_put(&cub->render_img, cub->render_img.x, start, get_color_img(&img, start, cub->render_img.x));
	}
}