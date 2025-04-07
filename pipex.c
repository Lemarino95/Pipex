/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/07 11:45:31 by lemarino         ###   ########.fr       */
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
		return(close(pipefd[1]), exit(2));
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
		return(close(pipefd[0]),  exit(3));
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_cmd(av[ac - 2], envp);
	exit(127);
}

/* void	firstborn(char *av[], char **envp)
{
	int	pipefd[2];
	int	id1;
	int	id2;

	if (-1 == pipe(pipefd))
		return (print_err(RED"Failed to create pipe"), exit(4));
	id1 = fork();
	if (0 == id1)
		first_cmd_process(av, envp, pipefd);
	id2 = fork();
	if (0 == id2)
		last_cmd_process(av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
} */

int	main(int ac, char *av[], char **envp)
{
	int	pipefd[2];
	int	id1;
	int	id2;

	if (5 != ac)
		return (print_err("Invalid number of arguments", "\n"), 1);
	if (-1 == pipe(pipefd))
		return (print_err("Failed to create pipe", "\n"), 1);
	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed", "\n"), close(pipefd[0]), close(pipefd[1]), 1);
	else if (0 == id1)
		first_cmd_process(av, envp, pipefd);
	id2 = fork();
	if (id2 < 0)
		return (print_err("Fork failed", "\n"), close(pipefd[0]), close(pipefd[1]), 1);
	else if (0 == id2)
		last_cmd_process(ac, av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while(waitpid(-1, NULL, 0) > 0)
		;
}
