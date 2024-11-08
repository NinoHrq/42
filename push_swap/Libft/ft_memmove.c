/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:58:03 by nharraqi          #+#    #+#             */
/*   Updated: 2024/05/26 15:31:31 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmps;
	char	*tmpd;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	tmps = (char *)src;
	tmpd = (char *)dst;
	if (tmps > tmpd)
	{
		i = 0;
		while (i < len)
		{
			tmpd[i] = tmps[i];
			i++;
		}
	}
	else
	{
		while (len--)
			tmpd[len] = tmps[len];
	}
	return (dst);
}
