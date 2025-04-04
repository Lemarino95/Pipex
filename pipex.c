/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/04 18:50:00 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char *av[], char **envp, int *pipefd)
{
	int		infile;

	close(pipefd[0]);
	infile = open(av[1], O_RDONLY);
	if (-1 == infile)
		return(close(pipefd[1]), perror(RED"Invalid input file"), exit(0));
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_cmd(av[2], envp, "First");
}

void	daddy_process(char *av[], char **envp, int *pipefd)
{
	int		outfile;

	close(pipefd[1]);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == outfile)
		return(close(pipefd[0]), perror(RED"Invalid output file"), exit(0));
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_cmd(av[3], envp, "Second");
}

int	main(int ac, char *av[], char **envp)
{
	int	pipefd[2];
	int	id;

	if (5 != ac)
		return (perror(RED"Invalid number of arguments"), 0);
	if (-1 == pipe(pipefd))
		return (perror(RED"Failed to create pipe"), 0);
	id = fork();
	if (id < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (perror(RED"Fork failed"), 0);
	}
	if (0 == id)
		child_process(av, envp, pipefd);
	daddy_process(av, envp, pipefd);
}
