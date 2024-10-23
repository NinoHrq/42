/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:28:15 by nharraqi          #+#    #+#             */
/*   Updated: 2024/05/25 19:06:01 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (n > 0)
	{
		if (len + 1 < n)
		{
			ft_memcpy(dst, src, len + 1);
		}
		else
		{
			ft_memcpy(dst, src, n - 1);
			dst[n - 1] = '\0';
		}
	}
	return (len);
}
