void ft_putnbr(int nbr)
{
	int n;
	char digit;

	n = nbr;
	if (n < 0)
	{
		n = -n;
		write(1, '-', 1);
	}
	if (n > 9)
		ft_putnbr(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);	
}

int main (int ac, char **av)
{
	(void)av;

	ft_putnbr(ac - 1);
	write(1, "\n", 1);
	return(0);
}