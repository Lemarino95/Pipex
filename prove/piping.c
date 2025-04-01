#include "../pipex.h"

int	main()
{
	int	fd[2];// fd[0]: read; fd[1]: write
	if (pipe(fd) == -1)
		return (2);

	int	id = fork();
	if (-1 == id)
		return (2);
	// int	id2 = fork();
	
	int aspe = wait(NULL);//processo figlio deve finire prima del padre
	printf("processo %d, Pid: %d, PPid: %d\n", id, getpid(), getppid());
	
	if (0 == id){
		close(fd[0]);//Non serve perche' stiamo solo scrivendo
		int x;
		printf("Input a number to child: ");
		scanf("%d", &x);
		if(-1 == write(fd[1], &x, sizeof(int)))
			return(printf("Error in writing from child!\n"), 2);
		close(fd[0]);
	}
	else{
		close(fd[1]);///Non serve perche' stiamo solo leggendo
		int	y;
		if (-1 == read(fd[0], &y, sizeof(int)))
			return (printf("Error reading in parent from child\n"), 2);
		y = y * 4;
		close(fd[0]);
		printf("Parent got %d from child\n", y);
	}
	if (aspe < 0)
		printf("Figlio terminato\n");
	else
		printf("processo %d terminato\n", aspe);
}

// parent id = child pid, child id = 0
// pid = Process ID
// ppid = Parent Proc ID, ugale a Proc ID del processo padre