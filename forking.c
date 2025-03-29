#include "pipex.h"

int	main()
{
	int	id;
	int	id2;

	id = fork();
	printf("hello from first fork %d\n", id);
	if (id == 0)
	{
		id2 = fork();
		printf("hello from second fork %d\n", id2);
	}

}