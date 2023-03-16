/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:26:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/16 16:56:47 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_cub *vars)
{
	exit_free(vars, 0, "Exit Program Succesfully");
	return (0);
}

void	free_imgs(t_cub *data)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (data->img.wall[i].ptr)
			mlx_destroy_image(data->mlx, data->img.wall[i].ptr);
		data->img.wall[i].ptr = 0;
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (data->sprites[i].ptr)
			mlx_destroy_image(data->mlx, data->sprites[i].ptr);
		data->sprites[i].ptr = 0;
		i++;
	}
	if (data->screen.ptr)
		mlx_destroy_image(data->mlx, data->screen.ptr);
	data->screen.ptr = 0;
}

void	free_mlx(t_cub	*data)
{
	free_imgs(data);
	if (data->win != NULL)
	{
		mlx_destroy_display(data->mlx);
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		data->mlx = NULL;
		data->win = NULL;
	}
	else if (data->mlx != NULL)
	{
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	exit_prs(t_prs *data, int status, char *str)
{
	if (data)
	{
		if (data->file)
			alloc().free_matrix((void **)data->file);
		if (data->floor_c)
			alloc().free_array((void *)data->floor_c);
		if (data->color_c)
			alloc().free_array((void *)data->color_c);
	}
	exit_free(cube(), status, str);
}

void	exit_free(t_cub *data, int status, char *str)
{
	int	i;

	i = -1;
	if (status)
		printf("Error: %s\n", str);
	else
		printf("%s\n", str);
	if (data->map.mtx)
	{
		alloc().free_matrix((void **)data->map.mtx);
		data->map.mtx = 0;
	}
	if (data->img.path)
	{
		while (++i < 4)
			if (data->img.path[i])
				alloc().free_array((void *) data->img.path[i]);
		free(data->img.path);
	}
	free_mlx(data);
	exit(status);
}
