#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int ft_atoi(char *str)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i])
	{
		while(str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while(str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + str[i] - 48;
			i++;
		}
		res *= sign;
	}
	return(res);
}

void ft_putnbr(int nbr)
{
	unsigned int n;

	n = nbr;
	if (nbr < 0)
	{
		n = -n;
		ft_putchar ('-');
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int is_prime(int num)
{
	int i;

	i = 2;
	if (num <= 1)
		return (0);
	while(i * i <= num)
	{
		if (num % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int nbr;
		int sum;

		sum = 0;
		nbr = ft_atoi(av[1]);
		while(nbr > 0)
		{
			if (is_prime(nbr))
				sum += nbr;
			nbr--;
		}
		ft_putnbr(sum);
	}
	else
		ft_putnbr(0);
	write(1, "\n", 1);
	return (0);
}