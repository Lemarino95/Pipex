#include "../pipex.h"

char	**free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	*find_pathname(char **envp, char *cmd)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		pathname = ft_strjoin(ft_strdup(paths[i]), "/");
		pathname = ft_strjoin(pathname, cmd);
		if (0 == access(pathname, F_OK | X_OK))
			return (free_dpc(paths), pathname);
		free(pathname);
		i++;
	}
	free_dpc(paths);
	return (NULL);
}

int	main(int ac, char *av[], char **envp)
{
	int		id1;
	int		pipefd1[2];
	char	**cmd1;
	char	**cmd2;
	
	if (5 != ac) {return (9);}
	if (-1 == pipe(pipefd1)) {return (2);}
	cmd1 = ft_split(av[2], ' '); if (!cmd1) {return (2);}
	cmd2 = ft_split(av[3], ' '); if (!cmd2) {return (2);}
	id1 = fork(); if (id1 < 0) {return (2);}
	
	if (0 == id1){
		char	*PATH1;
		close(pipefd1[0]);
		int infile = open(av[1], O_RDONLY);
		if (-1 == infile) {return (printf("No infile created...\n"), 2);}
		PATH1 = find_pathname(envp, cmd1[0]); if (!PATH1) {return (2);}

		dup2(infile, 0);//Sostituisce l'fd 1(standard output) con infile
		close(infile);
		dup2(pipefd1[1], 1);
		close(pipefd1[1]);
		execve(PATH1, cmd1, envp);// solo "cmd1"?
		printf(BRGREEN"Child didn't execute\n");//################
		free(PATH1);
	}

	else{
		char	*PATH2;
		close(pipefd1[1]);
		wait(NULL);
		int	outfile = open(av[4], O_WRONLY | O_CREAT, 0644);
		if (-1 == outfile) {return (printf("No outfile created...\n"), 2);}
		PATH2 = find_pathname(envp, cmd2[0]); if (!PATH2) {return (2);}
		dup2(pipefd1[0], 0);
		close(pipefd1[0]);
		dup2(outfile, 1);
		close(outfile);
		printf(BLACK_ON_WHITE"Papa takes over\n"NO_ALL);//################
		execve(PATH2, cmd2, envp);
		free(PATH2);
		free(cmd1);
		free(cmd2);
	}
}
