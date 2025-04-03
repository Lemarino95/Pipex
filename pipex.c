/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/03 21:40:21 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char **envp)
{
	int	pipefd[2];

	if (5 != ac)
		return (perror("Invalid number of arguments"), 0);
	if (-1 == pipe(pipefd))
		return (perror("Failed to create pipe"), 0);
	
}
