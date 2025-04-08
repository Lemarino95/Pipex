/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:01:50 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/08 11:41:11 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_err(char *s1, char *err_type)
{
	write(2, RED"", 5);
	write(2, s1, ft_strlen(s1));
	write(2, err_type, ft_strlen(err_type));
	write(2, NO_ALL"", 4);
}

// Looks for the path of the command "cmd" in the Environment (envp)
char	*find_pathname(char *cmd, char **envp)
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
	return (print_err(cmd, ": command not found.\n"), NULL);
}

// Executes a command with the given absolute or relative path
void	*execute_absrel_path(char *cmd, char **envp)
{
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (NULL);
	if (access(split_cmd[0], F_OK | X_OK | R_OK) != 0)
	{
		print_err(cmd, ": permission denied.\n");
		free_dpc(split_cmd);
		return (NULL);
	}
	execve(split_cmd[0], split_cmd, envp);
	print_err(cmd, ": command not executed.\n");
	return (free_dpc(split_cmd), NULL);
}

// If a '/' is present in the cmd string, an absolute/relative path was given
//  to the command from input and it won't be searched in the Environment
void	*execute_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**split_cmd;

	split_cmd = NULL;
	cmd_path = NULL;
	if (ft_strchr(cmd, '/'))
	{
		execute_absrel_path(cmd, envp);
		return (NULL);
	}
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (NULL);
	cmd_path = find_pathname(split_cmd[0], envp);
	if (!cmd_path)
		return (free_dpc(split_cmd), NULL);
	execve(cmd_path, split_cmd, envp);
	print_err(cmd, ": command not executed.\n");
	return (free(cmd_path), free_dpc(split_cmd), NULL);
}
