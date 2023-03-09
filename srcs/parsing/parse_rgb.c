/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_RGB.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/09 17:14:05 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	rgb_util(char *clr, t_parse *parse)
{
	int	n;
	
	n = string().atoi(clr);
	if (n > 255 || n < 0)
	{
		clean_parsing(parse);
		exit_free(new_cube(), 1, "Not a recognizable RGB range system");
	}
	return (n);
}

int	get_colors(char *clr, t_parse *parse)
{
	int	i;
	int	rgb[3];

	i = 0;
	rgb[i] = string().atoi(clr);
	if (rgb[0] > 255 || rgb[0] < 0)
	{
		clean_parsing(parse);
		exit_free(new_cube(), 1, "Not a recognizable RGB range system");
	}
	while (++i < 3)
	{
		while (string().isdig(*clr))
			clr++;
		if (*clr != ',')
		{
			clean_parsing(parse);
			exit_free(new_cube(), 1, "Not a recognizable RGB range system");
		}
		clr++;
		rgb[i] = rgb_util(clr, parse);
	}
	i = 255;
	return (i << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
