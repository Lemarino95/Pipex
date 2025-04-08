/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:14:29 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 20:18:39 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Closes all file descriptors and liberates the allocated memory
void	liberate_fdmatrix(int **fd_mrx, int i)
{
	int j;

	j = 0;
	while (j <= i)
	{
		close(fd_mrx[j][0]);
		close(fd_mrx[j][1]);
		free(fd_mrx[j]);
		j++;
	}
	free(fd_mrx);
}

/* void	close_fds(int **fd_mrx, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		close(fd_mrx[j][0]);
		close(fd_mrx[j][1]);
		j++;
	}
} */

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
				liberate_fdmatrix(fd_matrix, i);
				exit(0);
			}
		i++;
	}
	return (fd_matrix);
}
