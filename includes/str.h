/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:49:13 by mgranate_ls       #+#    #+#             */
/*   Updated: 2023/03/08 20:49:14 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdlib.h>
# include <limits.h>

typedef struct s_str	t_str;

struct s_str
{
	int		(*len)(char *s, char c);
	int		(*strncmp)(char *s1, char *s2, size_t n);
	long	(*atoi)(char *s);
	char	*(*strchr)(char *s, char c);
	char	*(*strrchr)(char *s, char c);
	char	*(*trim)(char *s1, char *set);
	int		(*isdig)(char c);
	int		(*ft_isspace)(char c);
	char	*(*itoa)(char *s, int *maxdig, int counter, int n);
	char	*(*substr)(char *s, unsigned int start, size_t len);
	char	*(*contains)(char *big, char *little, size_t len);
	int		(*ft_isalnum)(char c);
	char	*(*strdup)(char *s);
	char	*(*strjoin)(char *s1, char *s2);
	char	*(*strtrim)(char *s1, char *set);
};

t_str	string(void);

#endif