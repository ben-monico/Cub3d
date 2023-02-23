/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmonico <benmonico@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:36 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/23 19:23:41 by benmonico        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse	*parsing(void)
{
	static	t_parse	data;

	return(&data);
}

void	trim_ident(char *line, t_parse *parse, int ct)
{
	char	*trim;

	if (!line)
		exit_parse(parse, 1, "Identifier with no path");
	trim = string().strtrim(line, " /t/v/r/n");
	if (!trim)
		exit_parse(parse, 1, "Allocation In parsing Failed");
	if (ct == 4 || ct == 5)
	{
		if (ct == 4)
			parse->f_c = string().strdup(trim);
		else
			parse->c_c = string().strdup(trim);
		alloc().free_array(trim);
		return ;
	}	
	parse->path_to_img[ct] = string().strdup(trim);
	alloc().free_array(trim);
}

int	check_identifier(char *line, t_parse *parse, int ct)
{
	if (!string().strncmp("NO", line, 2) && ct == 0)
		trim_ident(line + 2, parse, ct);
	else if (!string().strncmp("SO", line, 2) && ct == 1)
		trim_ident(line + 2, parse, ct);
	else if (!string().strncmp("WE", line, 2) && ct == 2)
		trim_ident(line + 2, parse, ct);
	else if (!string().strncmp("EA", line, 2)  && ct == 3)
		trim_ident(line + 2, parse, ct);
	else if (!string().strncmp("F", line, 1) && ct == 4)
		trim_ident(line + 1, parse, ct);
	else if (!string().strncmp("C", line, 1) && ct == 5)
		trim_ident(line + 1, parse, ct);
	if (parse->f_c || parse->c_c || parse->path_to_img[ct])
		return (1);
	return (0);
}

int	get_path_img(t_parse *parse)
{
	int		i;
	int		j;
	int		ct;

	ct = 0;
	parse->path_to_img = alloc().calloc((5) * (sizeof(char *)));
	if (!parse->path_to_img)
		exit_parse(parse, 1, "Allocation Failed in Parsing Images");
	i = -1;
	while (parse->file[++i] && ct < 6)
	{
		j = -1;
		while (parse->file[i][++j])
		{
			if (!string().ft_isspace(parse->file[i][j]))
			{
				if (!check_identifier(parse->file[i] + j, parse, ct))
					exit_parse(parse, 1, "File Not Formated Correctly");
				ct++;
				break ;
			}
		}
	}
	return (i);
}

void	parse_file(t_parse *parse)
{
	int	i;
	
	i = get_path_img(parse);
	if (!get_map(parse->file + i, new_cub()))
		exit_parse(parse, 1, "Map Not Formated Correctly");
	//load_img(new_cub(), parse->path_to_img);
	new_cub()->img.colors[0] = get_colors(parse->f_c, parse);
	new_cub()->img.colors[1] = get_colors(parse->c_c, parse);
	//DONT FORGET - FUNCTION MISSING: send_f_c.&&.c_c to cub struct
}
