/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:52:59 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/07 19:50:26 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd_process(char *av[], char **envp, int *pipefd)
{
	int		infile;

	close(pipefd[0]);
	infile = open(av[1], O_RDONLY);
	if (-1 == infile)
	{
		print_err(av[1], ": Permission denied.\n");
		return (close(pipefd[1]), exit(2));
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_cmd(av[2], envp);
	exit(0);
}

void	last_cmd_process(int ac, char *av[], char **envp, int *pipefd)
{
	int		outfile;

	close(pipefd[1]);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == outfile)
	{
		print_err(av[ac - 1], ": Permission denied.\n");
		return (close(pipefd[0]), exit(3));
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_cmd(av[ac - 2], envp);
	exit(127);
}
