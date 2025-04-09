/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:51:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/09 16:27:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

typedef struct s_pipes
{
	int	**fdmrx;
	int	i;
}	t_pipes;

/*                   middle_cmds_bonus.c                 */
// Creates a child process for each command to be executed.
void	nursery(int ac, char *av[], char **envp, int **fd_mrx);

/*                   utils_bonus.c                 */
int		**fd_matrix_creator(int ac);
void	liberate_fdmatrix(int **mrx, int i);
// void	close_fds(int **fd_mrx, int i);

#endif
//valchild --suppressions=supp.supp 
