/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/04 18:34:45 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_pathname(char **envp, char *cmd)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		pathname = ft_strjoin(ft_strdup(paths[i]), "/");
		pathname = ft_strjoin(pathname, cmd);
		if (!pathname)
			return (free_dpc(paths), NULL);
		if (0 == access(pathname, F_OK | X_OK))
			return (free_dpc(paths), pathname);
		free(pathname);
		i++;
	}
	free_dpc(paths);
	perror(RED"Path not found or invalid");
	return (ft_printf("Command \"%s\" not executed.\n", cmd), NULL);
}

void	execute_cmd(char *cmd, char **envp, char *numcmd)
{
	char	*PATH;
	char	**split_cmd;

	split_cmd = NULL;
	PATH = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK | R_OK) != 0)
			return (perror(RED"Invalid path"), exit(0));
		split_cmd = ft_split(cmd, ' ');
		execve(cmd, split_cmd, envp);
		ft_printf(RED"%s command not executed\n", numcmd);
		return (free_dpc(split_cmd), exit(0));
	}
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return;
	PATH = find_pathname(envp, split_cmd[0]);
	if (!PATH)
		return (free_dpc(split_cmd), exit(0));
	execve(PATH, split_cmd, envp);
	ft_printf(RED"%s command not executed\n", numcmd);
	return (free(PATH), free_dpc(split_cmd), exit(0));
}
