/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:22:03 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/16 16:45:30 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prs.h>

void	clean_parsing(t_prs *data)
{
	if (data->file)
		alloc().free_matrix((void **)data->file);
	if (data->floor_c)
		alloc().free_array((void *)data->floor_c);
	if (data->color_c)
		alloc().free_array((void *)data->color_c);
}

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
	{
		close(fd);
		exit_free(data, 1, "The argument passed must exist");
	}
	return (fd);
}

char	**read_lines(char **map, int fd, int ct, char *file_name)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ct++;
		alloc().free_array(line);
	}
	map = alloc().calloc((ct + 1) * (sizeof(char *)));
	close(fd);
	fd = open(file_name, O_RDONLY);
	map[ct] = NULL;
	ct = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[ct++] = string().strdup(line);
		alloc().free_array(line);
	}
	close(fd);
	return (map);
}

int	read_file(t_cub *cube, char *file_name, int ac)
{
	int		fd;
	t_prs	*prs;

	if (ac != 2)
		exit_free(cube, 1, "Invalid arg count");
	prs = parsing();
	if (!string().strrchr(file_name, '.') \
	|| string().strncmp(string().strrchr(file_name, '.'), ".cub", 5) \
	|| !(*(string().strrchr(file_name, '.') - 1)) \
	|| *(string().strrchr(file_name, '.') - 1) == '/')
		exit_free(cube, 1, "Invalid File Extension");
	fd = open_file(cube, file_name);
	prs->file = read_lines(NULL, fd, 0, file_name);
	prs_file(prs);
	clean_parsing(prs);
	return (1);
}
