/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_maj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:50 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/18 15:07:38 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa_maj(unsigned int c)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789ABCDEF";
	count += ft_putnbr_base(c, base);
	return (count);
}
