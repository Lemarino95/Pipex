/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/05 19:21:38 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1_process(char *av[], char **envp, int *pipefd)
{
	int		infile;

	close(pipefd[0]);
	infile = open(av[1], O_RDONLY);
	if (-1 == infile)
	{
		perror(RED"zsh: ");
		return(close(pipefd[1]), exit(2));
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_cmd(av[2], envp, "First");
	exit(0);
}

void	cmd2_process(char *av[], char **envp, int *pipefd)
{
	int		outfile;

	close(pipefd[1]);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == outfile)
	{
		perror(RED"zsh: ");
		return(close(pipefd[0]),  exit(3));
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_cmd(av[3], envp, "Second");
	exit(127);
}

/* void	firstborn(char *av[], char **envp)
{
	int	pipefd[2];
	int	id1;
	int	id2;

	if (-1 == pipe(pipefd))
		return (perror(RED"Failed to create pipe"), exit(4));
	id1 = fork();
	if (0 == id1)
		cmd1_process(av, envp, pipefd);
	id2 = fork();
	if (0 == id2)
		cmd2_process(av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
} */

int	main(int ac, char *av[], char **envp)
{
	int	pipefd[2];
	int	id1;
	int	id2;

	if (5 != ac)
		return (perror(RED"Invalid number of arguments"), 1);
	if (-1 == pipe(pipefd))
		return (perror(RED"Failed to create pipe"), 1);
	id1 = fork();
	if (id1 < 0)
		return (perror("Fork failed"), close(pipefd[0]), close(pipefd[1]), 1);
	else if (0 == id1)
		cmd1_process(av, envp, pipefd);
	id2 = fork();
	if (id2 < 0)
		return (perror("Fork failed"), close(pipefd[0]), close(pipefd[1]), 1);
	else if (0 == id2)
		cmd2_process(av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while(waitpid(-1, NULL, 0) > 0)
		;
}
