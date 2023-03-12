/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:26:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/12 19:30:26 by mgranate_ls      ###   ########.fr       */
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
		while (++i < 8 && data->img.wall[i].ptr)
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
	if (data->screen.ptr)
	{
		mlx_destroy_image(data->mlx, data->screen.ptr);
		data->screen.ptr = 0;
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

void	exit_prs(t_prs *data, int status, char *str)
{
	int	i;

	if (status)
		printf("Error: %s\n", str);
	else
		printf("%s\n", str);
	if (data)
	{
		if (data->file)
			alloc().free_matrix((void **)data->file);
		if (data->path_to_img)
		{
			i = -1;
			while (++i < 4)
				alloc().free_array((void *)data->path_to_img[++i]);
		}
		if (data->floor_c)
			alloc().free_array((void *)data->floor_c);
		if (data->color_c)
			alloc().free_array((void *)data->color_c);
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
