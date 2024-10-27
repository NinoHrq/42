#include <unistd.h>

int	main(int ac, char **av)
{
		int i;
		int j;

	if (ac > 1)
	{
		i = 1;
		while (av[i])
		{
			j = 0;
			if (av[i][j] >= 'a' && 'z' >= av[i][j])
			{
				av[i][j] -= 32;
				write(1, &av[i][j], 1);
				j++;
			}
			while (av[i][j])
			{
				if (av[i][j] >= 'A' && 'Z' >= av[i][j])
					av[i][j] += 32;
				if ((av[i][j] >= 'a' && 'z' >= av[i][j]) && (av[i][j - 1] == ' '
						|| av[i][j - 1] == '\t'))
					av[i][j] -= 32;
				write(1, &av[i][j], 1);
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
