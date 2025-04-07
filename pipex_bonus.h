/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:51:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/07 19:51:58 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

typedef struct s_pipes
{
	int	**fdmrx;
	int	i;
}	t_pipes;

/*>>>>>>>>>>>>>>>>>>>>>> utils.c <<<<<<<<<<<<<<<<<<<<<*/
int		**fd_matrix_creator(int ac);
void	liberate_matrix(int **mrx, int i);

# include "pipex.h"

#endif
//valchild --suppressions=supp.supp ./pipex testfile.txt "ls" "grep p" "wc -l" floggo.txt