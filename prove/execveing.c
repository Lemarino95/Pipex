#include "../pipex.h"

int	main(int ac, char *av[], char **envp)
{
	int	id;
	int i = 0;

	char *PATH = {"/usr/bin/ls"};
	id = fork();
	printf("hello from proc %d\n", id);
	if (0 == id){
		// int testfile = open("testfile.txt", O_WRONLY | O_CREAT, 0644);
		// if (-1 == testfile) {return (printf("No file created...\n"),2);}
		// else {printf("\"testfile.txt\" created! -> fd %d\n", testfile);}

		// dup2(testfile, 1);//Sostituisce l'fd 1(standard output) con testfile

		execve(PATH, &av[1], envp);
		printf(BRGREEN"Child didn't execute\n");
	}
	else{
		wait(NULL);
		printf(BLACK_ON_WHITE"Papa takes over\n"NO_ALL);
	}
}