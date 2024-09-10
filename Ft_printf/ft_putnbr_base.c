/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:08:05 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/11 11:57:40 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	int	baseval;
	int	count;

	baseval = 0;
	count = 0;
	while (base[baseval])
		++baseval;
	if (nbr >= (unsigned long)baseval)
	{
		count += ft_putnbr_base(nbr / baseval, base);
		count += ft_putnbr_base(nbr % baseval, base);
	}
	else
		count += ft_putchar (base[nbr]);
	return (count);
}
