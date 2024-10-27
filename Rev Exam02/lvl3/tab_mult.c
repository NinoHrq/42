#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + str[i] - 48;
			i++;
		}
		res *= sign;
	}
	return (res);
}
void	ft_putnbr(int nbr)
{
	unsigned int	n;

	n = nbr;
	if (nbr < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}
int	main(int ac, char **av)
{
	int	i;
	int	res;
	int	nbr;

	if (ac == 2)
	{
		i = 1;
		nbr = ft_atoi(av[1]);
		if (nbr > 0)
		{
			while (i <= 9)
			{
				res = i * nbr;
				ft_putnbr(i);
				write(1, " x ", 3);
				ft_putnbr(nbr);
				write(1, " = ", 3);
				ft_putnbr(res);
				write(1, "\n", 1);
				i++;
			}
		}
	}
	else
		write(1, "\n", 1);
}
