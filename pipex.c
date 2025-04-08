/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 19:23:29 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char **envp)
{
	int	pipefd[2];
	int	id1;
	int	id2;

	if (5 != ac)
		return (print_err("Invalid number of arguments.", "\n"), 1);
	if (-1 == pipe(pipefd))
		return (print_err("Failed to create pipe.", "\n"), 1);
	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"), \
								close(pipefd[0]), close(pipefd[1]), 1);
	else if (0 == id1)
		first_cmd_process(av[1], av[2], envp, pipefd);
	id2 = fork();
	if (id2 < 0)
		return (print_err("Fork failed for id2.", "\n"), \
								close(pipefd[0]), close(pipefd[1]), 1);
	else if (0 == id2)
		last_cmd_process(ac, av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while (waitpid(-1, NULL, 0) > 0)
		;
}
