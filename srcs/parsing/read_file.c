/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:22:03 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/20 22:33:18 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>


void	clean_parsing(t_parse *data)
{
	if (data->file)
		alloc().free_matrix((void **)data->file);
	if (data->path_to_img)
		alloc().free_matrix((void **)data->path_to_img);
	if (data->f_c)
		alloc().free_array((void *)data->f_c);
	if (data->c_c)
		alloc().free_array((void *)data->c_c);
	//free_mlx(data);
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
		exit_free(data, 1, "The argument passed must exist");
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
	return (map);
}

int	read_file(t_cub *cube, char *file_name, int ac)
{
	int		fd;
	t_parse	*parse;

	if (ac != 2)
		exit_free(cube, 1, "Invalid arg count");
	parse = parsing();
	fd = open_file(cube, file_name);
	if (!string().strrchr(file_name, '.') || string().strncmp(string().strrchr(file_name, '.'), ".cub", 5))
		exit_free(cube, 1, "Invalid File Extension");
	parse->file = read_lines(NULL, fd, 0, file_name);
	parse_file(parse);
	clean_parsing(parse);
	return (1);
}
