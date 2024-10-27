void	sort_in_tab(int *tab, unsigned int len)
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
}

#include <stdio.h>

void	sort_in_tab(int *tab, unsigned int len);

int	main(void)
{
	int tab[] = {5, 2, 9, 1, 5, 6, 1, 2, 5, -1, 4};                 
		// tableau d'exemple avec des valeurs non triées
	unsigned int len = sizeof(tab) / sizeof(tab[0]);
		// calcul de la longueur du tableau
	printf("Tableau avant tri :\n");
	for (unsigned int i = 0; i < len; i++)
		printf("%d ", tab[i]);
	printf("\n");
	// Appel de la fonction pour trier le tableau
	sort_in_tab(tab, len);
	printf("Tableau après tri :\n");
	for (unsigned int i = 0; i < len; i++)
		printf("%d ", tab[i]);
	printf("\n");
	return (0);
}
