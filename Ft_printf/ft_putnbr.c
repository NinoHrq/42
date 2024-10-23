/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:38:25 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/11 12:19:36 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	long	digit;
	long	count;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
		count++;
	}
	if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
	}
	digit = nb % 10 + '0';
	write(1, &digit, 1);
	count++;
	return (count);
}
