/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_min.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:39:34 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/08 15:42:57 by nharraqi         ###   ########.fr       */
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

int	ft_printhexa_min(int c, char *base)
{
	base = "0123456789abcdef";
	ft_putnbr_base(c, base);
	return (ft_strlen(c));
}
