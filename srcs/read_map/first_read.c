/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:22:03 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/16 21:44:30 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	open_file(t_cub *data, char *name)
{
	int	fd;

	fd = open(name, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit_free(data, 1, "The argument passed must not be a directory");
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit_free(data, 1, "The argument passed must exist");
	return (fd);
}

int	read_file(t_cub *cube, char *file_name)
{
	char	*line;
	int		fd;
	
	fd = open_file(cube, file_name);
	line = get_next_line(fd);
	printf("line: %s\n", line);
	return (1);
}
