/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:14:29 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/07 19:43:12 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	liberate_matrix(int **mrx, int i)
{
	int j;

	j = 0;
	while (j <= i)
	{
		free(mrx[j]);
		j++;
	}
	free(mrx);
}

int	**fd_matrix_creator(int ac)
{
	int	**fd_matrix;
	int	i;

	i = 0;
	fd_matrix = ft_calloc((ac - 3), sizeof(int *));
	if (!fd_matrix)
		exit(0);
	while (i < (ac - 4))
	{
		fd_matrix[i] = ft_calloc(2, sizeof(int));
		if (!fd_matrix[i])
			{
				liberate_matrix(fd_matrix, i);
				exit(0);
			}
		i++;
	}
	return (fd_matrix);
}
