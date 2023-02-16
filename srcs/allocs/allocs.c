/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranate_ls <mgranate_ls@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:04:53 by mgranate          #+#    #+#             */
/*   Updated: 2023/02/15 18:49:32 by mgranate_ls      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocs.h>

/*
	It will free a matrix
*/
void	free_matrix(void **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return ;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	matrix = NULL;
}

/*
	It will free an array
*/

void	free_array(void *array)
{
	if (!array)
		return ;
	free(array);
	array = NULL;
}

/*
	Sets n bytes of a void pointer to 0
*/
static void	*ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = -1;
	while (++i < n)
		str[i] = 0;
	return (s);
}

/*
	Allocates a memory a sets all bytes to 0
*/
void	*ft_calloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (ptr);
	ptr = ft_bzero(ptr, size);
	return (ptr);
}

/*
	Calls a struct with functions for allocation and deallocates memory
*/

t_allocs	alloc(void)
{
	static t_allocs	allocs = {
		ft_calloc, free_matrix, free_array
	};

	return (allocs);
}
