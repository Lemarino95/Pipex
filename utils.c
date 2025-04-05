/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/05 19:44:12 by lemarino         ###   ########.fr       */
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
	return (perror(RED"zsh: command not found"), NULL);//ft_printf("Invalid path for %s command.\n", cmd)
}

void	*execute_cmd(char *cmd, char **envp, char *numcmd)
{
	char	*PATH;
	char	**split_cmd;

	split_cmd = NULL;
	PATH = NULL;
	if (ft_strchr(cmd, '/'))
	{
		split_cmd = ft_split(cmd, ' ');
		if (!split_cmd)
			return (NULL);
		if (access(split_cmd[0], F_OK | X_OK | R_OK) != 0)
			return (perror(RED"Invalid path"), free_dpc(split_cmd), NULL);//zsh: permission denied: cmd ??
		execve(split_cmd[0], split_cmd, envp);
		ft_printf("%s command not executed\n", numcmd);
		return (free_dpc(split_cmd), NULL);
	}
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return(NULL);
	PATH = find_pathname(envp, split_cmd[0]);
	if (!PATH)
		return (free_dpc(split_cmd), NULL);
	execve(PATH, split_cmd, envp);
	ft_printf("%s command not executed\n", numcmd);
	return (free(PATH), free_dpc(split_cmd), NULL);
}
