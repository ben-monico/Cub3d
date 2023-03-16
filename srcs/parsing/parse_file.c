/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:36 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/10 16:51:11 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prs.h>
#include <unistd.h>
#include <fcntl.h>

t_prs	*parsing(void)
{
	static t_prs	data;

	return (&data);
}

int	trim_ident(char *line, t_prs *prs, int ct)
{
	char	*trim;

	if (!line)
		exit_prs(prs, 1, "Identifier with no path");
	trim = string().strtrim(line, " \t\v\r\n");
	if (!trim)
		exit_prs(prs, 1, "Allocation In parsing Failed");
	if (ct == 4)
	{
		if (!prs->floor_c && string().strchr(trim, 'F'))
			prs->floor_c = string().strdup(trim);
		else if (!prs->color_c && string().strchr(trim, 'C'))
			prs->color_c = string().strdup(trim);
		alloc().free_array(trim);
		return (1);
	}
	if (!cube()->img.path[ct])
		cube()->img.path[ct] = string().strdup(trim);
	alloc().free_array(trim);
	return (1);
}

int	check_identifier(char *line, t_prs *prs)
{
	static int	ctr;

	if (ctr > 4)
		return (0);
	if (!string().strncmp("NO ", line, 3))
		return (trim_ident(line + 2, prs, 0));
	else if (!string().strncmp("SO ", line, 3))
		return (trim_ident(line + 2, prs, 1));
	else if (!string().strncmp("WE ", line, 3))
		return (trim_ident(line + 2, prs, 2));
	else if (!string().strncmp("EA ", line, 3))
		return (trim_ident(line + 2, prs, 3));
	else if (!string().strncmp("F ", line, 1)
		|| !string().strncmp("C ", line, 1))
		return (trim_ident(line, prs, 4));
	if (prs->floor_c || prs->color_c)
		return (1);
	return (0);
}

int	get_path_img(t_prs *prs)
{
	int		i;
	int		j;
	int		ct;

	ct = 0;
	cube()->img.path = alloc().calloc((sizeof(char *) * 5));
	if (!cube()->img.path)
		exit_prs(prs, 1, "Allocation Failed in Parsing Images");
	cube()->img.path[4] = NULL;
	i = -1;
	while (prs->file[++i] && ct < 6)
	{
		j = -1;
		while (prs->file[i][++j])
		{
			if (!string().ft_isspace(prs->file[i][j]))
			{
				if (!check_identifier(prs->file[i] + j, prs))
					exit_prs(prs, 1, "File Not Formated Correctly");
				ct++;
				break ;
			}
		}
	}
	return (i);
}

void	prs_file(t_prs *prs)
{
	int	i;
	int	c;
	int	f;
	int	fd;

	i = get_path_img(prs);
	if (!get_map(prs->file + i, cube()))
		exit_prs(prs, 1, "Map Not Formated Correctly");
	i = -1;
	while (++i < 4)
	{
		if (!cube()->img.path[i])
			exit_prs(prs, 1, "Missing a Texture on the wall!");
		fd = open(cube()->img.path[i], O_RDONLY);
		if (fd == -1 && close(fd))
			exit_prs(prs, 1, "Texture File does not exist!");
		else
			close(fd);
	}
	if (!prs->floor_c || !prs->color_c)
		exit_prs(prs, 1, "Missing Floor or Celling Color!");
	f = get_colors(prs->floor_c + 1, prs);
	c = get_colors(prs->color_c + 1, prs);
	cube()->img.colors[0] = f;
	cube()->img.colors[1] = c;
}
