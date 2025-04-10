/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:48:00 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/09 16:30:47 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize_commands(int ac, char **av, char **envp)
{
	int		pipefd[2];
	int		id1;
	int		id2;

	if (pipe(pipefd) < 0)
		exit(0);
	id1 = fork();
	if (id1 < 0)
		return (close(pipefd[1]), close(pipefd[0]), exit(0));
	else if (0 == id1)
		first_cmd_process("here_doc.txt", av[3], envp, pipefd);
	id2 = fork();
	if (id2 < 0)
		return (close(pipefd[1]), close(pipefd[0]), exit(0));
	if (0 == id2)
		last_cmd_process(ac, av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
}

// Writes the input text in a HereDoc file and deletes it after
//  the commands have been run
void	here_docking(int ac, char **av, char **envp)
{
	char	*limiter;
	char	*str;
	int		here_doc_fd;

	limiter = ft_strjoin(ft_strdup(av[2]), "\n");
	here_doc_fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (dup2(here_doc_fd, STDOUT_FILENO) < 0)
		return (free(limiter), exit(0));
	close(here_doc_fd);
	str = get_next_line(0);
	while (ft_strcmp(str, limiter) != 0)
	{
		ft_printf("%s", str);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	free(limiter);
	initialize_commands(ac, av, envp);
	while (waitpid(-1, NULL, 0) > 0)
		;
	unlink("here_doc.txt");
	exit(0);
}

int	main(int ac, char *av[], char **envp)
{
	int	**fd_mrx;

	if (ac < 5)
		return (print_err("Invalid number of arguments.", "\n"), 2);
	if (0 == ft_strcmp(av[1], "here_doc"))
		here_docking(ac, av, envp);
	fd_mrx = fd_matrix_creator(ac);
	if (!fd_mrx)
		return (print_err("Failed to create pipe matrix.", "\n"), 2);
	nursery(ac, av, envp, fd_mrx);
	liberate_fdmatrix(fd_mrx, ac - 5);
	while (waitpid(-1, NULL, 0) > 0)
		;
}
