/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:51:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 19:57:20 by lemarino         ###   ########.fr       */
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
//valchild --suppressions=supp.supp ./pipex_bonus testfile.txt "ls" "grep p" "wc -l" floggo.txt
// HEREDOC:
//cmd << LIMITER | cmd1 >> file  ===  wc -l << EOF | cat >> floggo.txt
// ~Se scrivo altro nella stessa riga del delimiter continua a leggere
// ~Delimiter puo essere composto da piu parole se tra virgolette. 
//       Devono essere usate tutte per concludere la lettura
// open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// unlink() per distruggere il file
