/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrhexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:50:13 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/11 12:15:42 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrhexa(void *ptr)
{
	unsigned long	tmp;
	int				count;

	count = 0;
	if (!ptr)
		count += write(1, "(nil)", 5);
	else
	{
		tmp = (unsigned long)ptr;
		count += write(1, "0x", 2);
		count += ft_putnbr_base(tmp, "0123456789abcdef");
	}
	return (count);
}
