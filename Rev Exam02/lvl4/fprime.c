#include<stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int i;
		int nbr;

		nbr = atoi(av[1]);
		i = 2;
		if(nbr == 1)
			printf("1");
		while (nbr >= i)
		{
			if(nbr % i == 0)
			{
				printf("%d", i);
				if(nbr == i)
					break;
				printf("*");
				nbr /= i;
				i = 2;
			}
			i++;			
		}
	}
	printf("\n");
	return(0);
}