int	max(int *tab, unsigned int len)
{
	unsigned int	i;
	int	j;

	i = 0;
	if (len == 0)
		return (0);
	j = 0;
	while (i < len)
	{
		if (tab[i] > j)
			j = tab[i];
		i++;
	}
	return (j);
}

#include <stdio.h>

int	main(void)
{
	int int_tab[] = {1, 3, 2, 10, 9, 123, 124, 561, 3256, 566, 122};
	printf("%d", max(int_tab, 11));
}