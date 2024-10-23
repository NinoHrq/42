#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i;
		int j;

		i = 0;
		while (av[1][i])
		{
			if (av[1][i] >= 65 && av[1][i] <= 77)
			{
				j = av[1][i] - 65;
				av[1][i] = 90 - j;
			}
			else if (av[1][i] >= 97 && av[1][i] <= 109)
			{
				j = av[1][i] - 97;
				av[1][i] = 122 - j;
			}
			else if (av[1][i] >= 78 && av[1][i] <= 90)
			{
				j = 90 - av[1][i];
				av[1][i] = 65 + j;
			}
			else if (av[1][i] >= 110 && av[1][i] <= 122)
			{
				j = 122 - av[1][i];
				av[1][i] = 97 + j;
			}
			write (1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
