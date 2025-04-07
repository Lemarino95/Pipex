/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:48:00 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/07 23:32:40 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_cmd_process(char *cmd, char **envp, int *pipefd1, int *pipefd2)
{
	int proc = getpid();//###########
	printf(MAGENTA"%d for cmd %s\n"NO_ALL, proc, cmd);
	
	//            Si ferma ma non funziona
	// close(pipefd1[0]);
	// close(pipefd2[1]);
	// dup2(pipefd2[0], STDIN_FILENO);
	// close(pipefd2[0]);
	// dup2(pipefd1[1], STDOUT_FILENO);
	// close(pipefd1[1]);

	//            Non si ferma mai
	close(pipefd1[1]);
	close(pipefd2[0]);
	dup2(pipefd1[0], STDIN_FILENO);
	close(pipefd1[0]);
	dup2(pipefd2[1], STDOUT_FILENO);
	close(pipefd2[1]);

	execute_cmd(cmd, envp);
	exit(0);
}

// Creates a child process for each command to be executed.
static void	nursery(int ac, char *av[], char **envp, int **fd_mrx)
{
	int	i;
	int	id1;
	int	id2;
	int	id3;

	i = 0;
	id1 = fork();
	if (-1 == pipe(fd_mrx[0]))
		return (print_err("Failed to create pipe.", "\n"));
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"));
	else if (0 == id1)
		first_cmd_process(av, envp, fd_mrx[0]);
	while (i < (ac - 5))
	{
		i++;
		if (-1 == pipe(fd_mrx[i]))
			return (print_err("Failed to create pipe.", "\n"));
		id2 = fork();
		if (id2 < 0)
			return (print_err("Fork failed for id2.", "\n"));
		else if (0 == id2)
			middle_cmd_process(av[i + 2], envp, fd_mrx[i - 1], fd_mrx[i]);
	}
	id3 = fork();
	if (id3 < 0)
		return (print_err("Fork failed for id3.", "\n"));
	else if (0 == id3)
		last_cmd_process(ac, av, envp, fd_mrx[i]);
	close_fds(fd_mrx, i);
}

int	main(int ac, char *av[], char **envp)
{
	int	**fd_mrx;
	int	fid;

	int proc = getpid();//###########
	printf(MAGENTA"%d for main\n"NO_ALL, proc);//###########
	
	if (ac < 5)
		return (print_err("Invalid number of arguments.", "\n"), 1);
	fd_mrx = fd_matrix_creator(ac);
	// if (-1 == pipe(fd_mrx))
	// 	return (print_err("Failed to create pipe.", "\n"), 1);
	fid = fork();
	if ( 0 == fid)
		nursery(ac, av, envp, fd_mrx);
	// close(pipefd[0]);
	// close(pipefd[1]);
	
	liberate_matrix(fd_mrx, ac - 4);
	int	pid;
	while ((pid = waitpid(-1, NULL, 0)) > 0)
		printf(BRGREEN"%d\n"NO_ALL, pid);
}
