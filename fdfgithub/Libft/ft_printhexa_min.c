/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_min.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:39:34 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/18 15:07:43 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa_min(unsigned int c)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	count += ft_putnbr_base(c, base);
	return (count);
}
