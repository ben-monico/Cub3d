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
	if (ct > 4)
		return (0);
	trim = string().strtrim(line, " \t\v\r\n");
	if (!trim)
		exit_prs(prs, 1, "Allocation In parsing Failed");
	if (string().strchr(trim, 'F') || string().strchr(trim, 'C'))
	{
		if (!prs->floor_c && string().strchr(trim, 'F'))
			prs->floor_c = string().strdup(trim);
		else if (!prs->color_c && string().strchr(trim, 'C'))
			prs->color_c = string().strdup(trim);
		alloc().free_array(trim);
		return (1);
	}
	prs->path_to_img[ct] = string().strdup(trim);
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
		return (trim_ident(line, prs, ctr));
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
	prs->path_to_img = alloc().calloc((5) * (sizeof(char *)));
	if (!prs->path_to_img)
		exit_prs(prs, 1, "Allocation Failed in Parsing Images");
	prs->path_to_img[4] = NULL;
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

	i = get_path_img(prs);
	if (!get_map(prs->file + i, cube()))
		exit_prs(prs, 1, "Map Not Formated Correctly");
	i = -1;
	cube()->img.path = alloc().calloc((sizeof(char *) * 5));
	while (++i < 4)
		parse_image(prs, i);
	if (!prs->floor_c || !prs->color_c)
		exit_prs(prs, 1, "Map Not Formated Correctly");
	f = get_colors(prs->floor_c + 1, prs);
	c = get_colors(prs->color_c + 1, prs);
	cube()->img.colors[0] = f;
	cube()->img.colors[1] = c;
}
