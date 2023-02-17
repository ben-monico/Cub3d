/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:36 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/02/17 15:48:31 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <parse.h>

t_parse	*parsing(void)
{
	static	t_parse	data;

	return(&data);
}

int	check_identifier(char *line, t_parse *parse, int ct)
{
	if (!string().strncmp("NO", line, 2) && ct == 0)
		parse->path_to_img[ct] = string().strdup(line);
	else if (!string().strncmp("SO", line, 2) && ct == 1)
		parse->path_to_img[ct] = string().strdup(line);
	else if (!string().strncmp("WE", line, 2) && ct == 2)
		parse->path_to_img[ct] = string().strdup(line);
	else if (!string().strncmp("EA", line, 2)  && ct == 3)
		parse->path_to_img[ct] = string().strdup(line);
	else if (!string().strncmp("F", line, 1) && ct == 4)
		parse->f_c = string().strdup(line);
	else if (!string().strncmp("C", line, 1) && ct == 5)
		parse->c_c = string().strdup(line);
	if (parse->f_c || parse->c_c || parse->path_to_img[ct])
		return (1);
	return (0);
}

t_parse	*get_path_img(t_parse *parse)
{
	int	i;
	int	j;
	int	ct;

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
	if (!get_map(parse->file + i, new_cube()))
		exit_parse(parse, 1, "Map Not Formated Correctly");
	return (parse);
}

void	parse_file(t_parse *parse)
{
	parse = get_path_img(parse);
	
	//exit_parse(parse, 1, "Exit Parsing Successfully");
}
