/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate <mgranate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:53:31 by mgranate          #+#    #+#             */
/*   Updated: 2023/03/06 18:35:35 by mgranate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str_utils.h>
#include <stdio.h>
/*
	This function evaluates if a char is space
*/

int	ft_isspace(char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

/*
	Returns a string without delimiters (the string set)
		at the beginning and the end
*/

char	*strtrim(char *s1, char *set)
{
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	// while (s1[start] && string().strchr(set, s1[start]))
	// 	start++;
	while(*s1 && string().strchr(set, *s1))
		s1++;
	end = ft_strlen(s1, -1) - 1;
	while (end >= 0 && s1[end] && string().strchr(set, s1[end]))
		end--;
	return (string().substr(s1, 0, end + 1));
}

/*
	Converts a string in to a number.
	See later for improvement because it returns a long int
*/

long	_atoi(char *s)
{
	long	n;
	long	sig;
	int		i;

	n = 0;
	i = -1;
	sig = 1;
	while (ft_isspace(s[++i]))
		;
	if (s[i] == '-' || s[i] == '+')
	{
		sig = (s[i] != '-') - (s[i] == '-');
		i++;
	}
	if (!isdig(s[i]))
		return (-1);
	while (isdig(s[i]))
		n = n * 10 + sig * (s[i++] - '0');
	return (n);
}

/*
	Itoa converts a number into a string the counter start at 1 because you
		 will always 1 digit
*/

char	*itoa(char *str, int *maxdig, int counter, int n)
{
	*maxdig = counter;
	if (n > 9 || n < -9)
		str = itoa(str, maxdig, counter + 1, n / 10);
	if (!str)
	{
		str = alloc().calloc(counter + 1 + (n < 0));
		if (!str)
			return (NULL);
		if (n < 0)
			str[0] = '-';
		str[counter + (n < 0)] = 0;
	}
	str[*maxdig - counter + (n < 0)] = (n % 10) * ((n > 0) - (n < 0)) + 48;
	return (str);
}

/*
	Compares two strings until n bytes
*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	if (n == 0)
		return (n);
	i = -1;
	while (s1[++i] && s2[i] && s1[i] == s2[i] && i < n)
		;
	return ((unsigned char)*(s1 + i - (n == i)) - \
	(unsigned char)*(s2 + i - (n == i)));
}
