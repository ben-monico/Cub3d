/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:26:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/09 20:01:05 by mgranate_ls      ###   ########.fr       */
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
		while (++i < 6 && data->img.wall[i].ptr)
		{
			mlx_destroy_image(data->mlx, data->img.wall[i].ptr);
			data->img.wall[i].ptr = 0;
		}
	}
	if (data->sprites[0].ptr)
	{	
		i = -1;
		while (++i < 2 && data->sprites[i].ptr)
		{
			mlx_destroy_image(data->mlx, data->sprites[i].ptr);
			data->sprites[i].ptr = 0;
		}
	}
	if (data->render_img.ptr)
	{
		mlx_destroy_image(data->mlx, data->render_img.ptr);
		data->render_img.ptr = 0;
	}
}

static void	free_mlx(t_cub	*data)
{
	free_imgs(data);
	if (data->win)
	{
		mlx_destroy_display(data->mlx);
		mlx_destroy_window(data->mlx, data->win);
		data->win = 0;
	}
	if (data->mlx)
	{
		free(data->mlx);
		data->mlx = NULL;
	}
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
		{
			alloc().free_matrix((void **)data->map.mtx);
			data->map.mtx = 0;
		}
		free_mlx(data);
	}
	if (data->img.path)
		alloc().free_matrix((void **) data->img.path);
	exit(status);
}
