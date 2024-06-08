/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:08:05 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/07 19:15:01 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_atoi(char *str)
{
	short	nbr;
	int		oddeven;
	int		i;

	nbr = 0;
	oddeven = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			oddeven++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr *= 10;
		nbr += str[i] - 48;
		i++;
	}
	if (oddeven % 2 == 0)
		return (nbr);
	return (-nbr);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putnbr(int nb, int baseval, char *symbol)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	if (n >= baseval)
	{
		ft_putnbr(n / baseval, baseval, symbol);
	}
	ft_putchar(symbol[n % baseval]);
}

static int	verif_dbl_char(char *symbol)
{
	int	i;
	int	j;

	i = 0;
	while (*(symbol + i))
	{
		j = i + 1;
		while (*(symbol + j))
		{
			if (*(symbol + i) == *(symbol + j))
				return (1);
			++j;
		}
		i++;
	}
	return (0);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	baseval;

	baseval = 0;
	while (base[baseval])
	{
		if (base[baseval] == '+' || base[baseval] == '-')
			return ;
		++baseval;
	}
	if (baseval < 2)
		return ;
	if (verif_dbl_char(base))
		return ;
	ft_putnbr(nbr, baseval, base);
}
