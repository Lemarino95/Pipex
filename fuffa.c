#include "pipex.h"

int main()
{
	char **arrs;

	arrs = ft_split("nun tiengo niente", ' ');
	free_dpc(arrs);
	
}