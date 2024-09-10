/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:20:31 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/11 12:22:44 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbru(unsigned int n)
{
	int				count;
	unsigned int	digit;

	count = 0;
	if (n > 9)
	{
		count += ft_putnbru(n / 10);
	}
	digit = n % 10 + '0';
	write(1, &digit, 1);
	count++;
	return (count);
}
