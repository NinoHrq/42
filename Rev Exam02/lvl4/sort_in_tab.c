void	sort_in_tab(int *tab, unsigned int len)
{
	unsigned int i;
	int tmp;

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
		i++;
	}
}