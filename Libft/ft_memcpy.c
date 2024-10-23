/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:25:43 by nharraqi          #+#    #+#             */
/*   Updated: 2024/05/21 15:52:50 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmpd;
	unsigned char	*tmps;

	if (dst == NULL && src == NULL)
		return (dst);
	tmpd = (unsigned char *) dst;
	tmps = (unsigned char *) src;
	while (n > 0)
	{
		*(tmpd++) = *(tmps++);
		n--;
	}
	return (dst);
}
