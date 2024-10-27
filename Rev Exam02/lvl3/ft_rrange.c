#include <stdlib.h>

void	rsort_in_tab(int *tab, unsigned int len);

int *ft_rrange(int start,
		int end)
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
	rsort_in_tab(tab, (unsigned int)len);
	return (tab);
}

void	rsort_in_tab(int *tab, unsigned int len)
{
	unsigned int	i;
	int				tmp;

	i = 0;
	while (i < (len - 1))
	{
		if (tab[i] < tab[i + 1])
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

#include <stdio.h>

int	main(void)
{
	int start = 3;
	int end = 10;
	int *tab;
	int len;
	int i;

	// Appel de la fonction
	tab = ft_rrange(start, end);

	// Calcul de la longueur pour affichage
	len = abs(end - start) + 1;

	// Vérification et affichage du tableau
	if (tab != NULL)
	{
		printf("Tableau généré et trié en ordre décroissant :\n");
		for (i = 0; i < len; i++)
			printf("%d ", tab[i]);
		printf("\n");

		// Libération de la mémoire allouée
		free(tab);
	}
	else
	{
		printf("Erreur d'allocation de mémoire.\n");
	}

	return (0);
}