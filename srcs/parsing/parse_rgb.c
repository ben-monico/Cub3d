/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:34:37 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/10 16:43:41 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prs.h>


int	rgb_util(char *clr, t_prs *prs)
{
	int	n;

	n = string().atoi(clr);
	if (n > 255 || n < 0)
	{
		clean_parsing(prs);
		exit_free(cube(), 1, "Not a recognizable RGB range system");
	}
	return (n);
}

int	get_colors(char *clr, t_prs *prs)
{
	int	i;
	int	rgb[3];

	i = 0;
	rgb[i] = atoi(clr);
	if (rgb[0] > 255 || rgb[0] < 0)
	{
		clean_parsing(prs);
		exit_free(cube(), 1, "Not a recognizable RGB range system");
	}
	while (++i < 3)
	{
		while (string().isdig(*clr) || string().ft_isspace(*clr))
			clr++;
		if (*clr != ',')
		{
			clean_parsing(prs);
			exit_free(cube(), 1, "Not a recognizable RGB range system");
		}
		clr++;
		rgb[i] = rgb_util(clr, prs);
	}
	i = 255;
	return (i << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
