/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:26:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/07 16:49:30 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_cub *vars)
{
	exit_free(vars, 0, "Exit Program Succesfully");
	return (0);
}

static void	free_imgs(t_cub *data)
{
	int	i;

	if (data->img.wall[0].ptr)
	{	
		i = -1;
		while (data->img.wall[++i].ptr)
		{
			printf("i: %d\n", i);
			printf("image: %p\n", data->img.wall[++i].ptr);
			mlx_destroy_image(data->mlx, data->img.wall[++i].ptr);
			alloc().free_array((void *)data->img.wall[++i].ptr);
			alloc().free_array((void *)data->img.wall[++i].addr);
		}
	}
}

static void	free_mlx(t_cub	*data)
{
	free_imgs(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	data->mlx = 0;
}

void	exit_parse(t_parse *data, int status, char *str)
{
	if (status)
		printf("Error: %s\n", str);
	else
		printf("%s\n", str);
	if (data)
	{
		if (data->file)
			alloc().free_matrix((void **)data->file);
		if (data->path_to_img)
			alloc().free_matrix((void **)data->path_to_img);
	}
	exit(status);
}

void	exit_free(t_cub *data, int status, char *str)
{
	if (status)
		printf("Error: %s\n", str);
	else
		printf("%s\n", str);
	if (data)
	{
		if (data->map.mtx)
			alloc().free_matrix((void **)data->map.mtx);
		free_mlx(data);
	}
	if (data->img.path)
		alloc().free_matrix((void **) data->img.path);
	exit(status);
}