#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		int i;
		int j;
		unsigned char lookup[256] = {0};

		i = 0;
		while (av[1][i])
		{
			if (!lookup[(unsigned char)av[1][i]])
				write(1, &av[1][i], 1);
			lookup[(unsigned char)av[1][i]] = 1;
			i++;
		}
		j = 0;
		while (av[2][j])
		{
			if (!lookup[(unsigned char)av[2][j]])
				write(1, &av[2][j], 1);
			lookup[(unsigned char)av[2][j]] = 1;
			j++;
		}
	}
	write(1, "\n", 1);
	return(0);
}