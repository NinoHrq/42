/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_maj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:50 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/08 15:41:35 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(int nb)
{
	int	i;

	i = 0;
	while (nb[i])
		i++;
	return (i);
}

int	ft_printhexa_maj(int c, char *base)
{
	base = "0123456789ABCDEF";
	ft_putnbr_base(c, base);
	return (ft_strlen(c));
}
