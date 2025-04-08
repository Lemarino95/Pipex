/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:52:59 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 19:26:43 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd_process(char *infile, char *cmd, char **envp, int *pipefd)
{
	int	file1fd;

	close(pipefd[0]);
	file1fd = open(infile, O_RDONLY);
	if (-1 == file1fd)
	{
		print_err(infile, ": Permission denied.\n");
		return (close(pipefd[1]), 0);
	}
	if (dup2(file1fd, STDIN_FILENO) < 0)
		return (close(pipefd[1]), close(file1fd), 0);
	close(file1fd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(cmd, envp);
	return (1);
	// exit(0);
}

int	last_cmd_process(int ac, char *av[], char **envp, int *pipefd)
{
	char	*outfile;
	int		file2fd;

	outfile = av[ac - 1];
	close(pipefd[1]);
	file2fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == file2fd)
	{
		print_err(av[ac - 1], ": Permission denied.\n");
		return (close(pipefd[0]), 0);
	}
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), close(file2fd), 0);
	close(pipefd[0]);
	if (dup2(file2fd, STDOUT_FILENO) < 0)
		return (close(file2fd), 0);
	close(file2fd);
	execute_cmd(av[ac - 2], envp);
	return (1);
	// exit(127);
}
