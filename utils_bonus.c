/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:14:29 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/07 22:51:32 by lemarino         ###   ########.fr       */
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

void	close_fds(int **fd_mrx, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		printf(BRCYAN"%d\n"NO_ALL, j);//###########
		close(fd_mrx[j][0]);
		close(fd_mrx[j][1]);
		j++;
	}
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
