/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:52:59 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 15:11:30 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd_process(char *av[], char **envp, int *pipefd)
{
	int	infile;

	close(pipefd[0]);
	infile = open(av[1], O_RDONLY);
	if (-1 == infile)
	{
		print_err(av[1], ": Permission denied.\n");
		return (close(pipefd[1]), 0);
	}
	if (dup2(infile, STDIN_FILENO) < 0)
		return (close(pipefd[1]), close(infile), 0);
	close(infile);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(av[2], envp);
	return (1);
	// exit(0);
}

int	last_cmd_process(int ac, char *av[], char **envp, int *pipefd)
{
	int	outfile;

	close(pipefd[1]);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == outfile)
	{
		print_err(av[ac - 1], ": Permission denied.\n");
		return (close(pipefd[0]), 0);
	}
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), close(outfile), 0);
	close(pipefd[0]);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		return (close(outfile), 0);
	close(outfile);
	execute_cmd(av[ac - 2], envp);
	return (1);
	// exit(127);
}
