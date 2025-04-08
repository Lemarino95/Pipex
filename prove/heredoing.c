#include "../pipex.h"

int	main()
{
	char	*txt;

	while(ft_strcmp(txt = get_next_line(0), "EOF\n") != 0)
		printf("%s", txt);
}
//cc heredoing.c ../libft/libft.a