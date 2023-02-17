/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:12:06 by mgranate          #+#    #+#             */
/*   Updated: 2023/02/17 15:48:11 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	read_line (char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!string().ft_isspace(line[i]))
			return (1);
	}
	return (0);
}

int	check_map_size(char	**file, int i)
{
	int	sz;

	sz = 0;
	while (file[i])
	{
		sz += read_line(file[i]);
		i++;
	}
	return (sz);
}

int	copy_map(char **file, int i, t_cub *cube)
{
	int	j;
	int	sz;
	int	l;

	sz = check_map_size(file, i);
	cube->map.mtx = alloc().calloc((sz + 1) * sizeof(char *));
	if (!cube->map.mtx)
		return (0);
	l = 0;
	while (file[i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (!string().ft_isspace(file[i][j]))
			{
				cube->map.mtx[l++] = file[i];
				break ;
			}
			if (!(file[i][1]) && l > 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	get_map(char **file, t_cub *cube)
{
	int	i;
	int	j;

	(void)cube;
	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (!string().ft_isspace(file[i][++j]))
			{
				if(!copy_map(file, i, cube))
					return (0);
				return (1);
			}
		}
	}
	return (1);
}
