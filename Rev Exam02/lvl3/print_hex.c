#include <unistd.h>

int ft_atoi(char *str)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	while(str[i] == '\t' || str[i] == ' ')
		i++;
	while(str[i] == '+' || str[i] == '-')
	{
		if(str[i] == '-')
			sign *= -1;
		i++;
	}
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
	}
	res = res * sign;
	return (res);
}

void print_hex(int nbr)
{
	char basehex[] = "0123456789abcdef";

	if(nbr > 16)
		print_hex(nbr / 16);
	write(1, &basehex[nbr % 16], 1);
}
int main(int ac, char **av)
{
	if(ac == 2)
	{
		int nbr;

		nbr = ft_atoi(av[1]);
		if(nbr >= 0)
			print_hex(nbr);
	}
	write(1, "\n", 1);
	return (0);
}