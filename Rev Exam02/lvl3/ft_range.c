#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	*tab;
	int	i;
	int	len;

	i = 0;
	if (start > end)
		len = start - end;
	else if (start < end)
		len = end - start;
	tab = malloc((len + 1) * sizeof(int));
	while (start != end)
	{
		tab[i++] = start;
		start += (start > end) ? -1 : 1;
	}
	tab[i] = start;
	return (*tab);
}

/*void	sort_in_tab(int *tab, unsigned int len)
{
	unsigned int	i;
	int				tmp;

	i = 0;
	while (i < (len - 1))
	{
		if (tab[i] > tab[i + 1])
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}*/
