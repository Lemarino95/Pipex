/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmds_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:36:36 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 19:37:06 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	middle_cmd_process(char *cmd, char **envp, int *pipefd1, int *pipefd2)
{
	// close(pipefd1[1]);
	close(pipefd2[0]);
	if (dup2(pipefd1[0], STDIN_FILENO) < 0)
		return (close(pipefd1[0]), close(pipefd2[1]), 0);
	close(pipefd1[0]);
	if (dup2(pipefd2[1], STDOUT_FILENO) < 0)
		return (close(pipefd2[1]), 0);
	close(pipefd2[1]);
	execute_cmd(cmd, envp);
	return (1);
	// exit(0);
}

// Creates a child process and a pipe for each command to be executed
//  between the first and last.
static int	middle_child_generator(int ac, char **av, char **envp, int **fd_mrx)
{
	int	id2;
	int	i;

	i = 0;
	while (i < (ac - 5))
	{
		i++;
		if (-1 == pipe(fd_mrx[i]))
			return (print_err("Failed to create pipe.", "\n"), i);
		id2 = fork();
		if (id2 < 0)
			return (print_err("Fork failed for id2.", "\n"), \
							close(fd_mrx[i][0]), close(fd_mrx[i][1]), i - 1);
		else if (0 == id2)
			middle_cmd_process(av[i + 2], envp, fd_mrx[i - 1], fd_mrx[i]);
		close(fd_mrx[i][1]);
	}
	return (i);
}

// Creates a child process for each command to be executed.
void	nursery(int ac, char *av[], char **envp, int **fd_mrx)
{
	int	i;
	int	id1;
	int	id3;

	i = 0;
	if (-1 == pipe(fd_mrx[0]))
		return (print_err("Failed to create pipe.", "\n"));
	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"));
	if (0 == id1)
		first_cmd_process(av[1], av[2], envp, fd_mrx[0]);
	close(fd_mrx[i][1]);
	i = middle_child_generator(ac, av, envp, fd_mrx);
	id3 = fork();
	if (id3 < 0)
		return (print_err("Fork failed for id3.", "\n"));
	else if (0 == id3)
		last_cmd_process(ac, av, envp, fd_mrx[i]);
	// close_fds(fd_mrx, i);
}
