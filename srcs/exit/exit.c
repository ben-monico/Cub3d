/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:26:04 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 03:16:29 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	free_imgs(t_cub *data)
{
	int	i;

	if (data->img.img)
	{
		i = -1;
		while (data->img.img[++i])
			mlx_destroy_image(data->win, data->img.img[i]);
		alloc().free_array((void *)data->img.img);
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
}

int	free_ob(void *v)
{
	if (v == NULL)
		return (1);
	free(v);
	return (1);
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
	exit(status);
}