/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:00:45 by tmilin            #+#    #+#             */
/*   Updated: 2024/05/30 15:01:45 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_tmp = (unsigned char *) dst;
	src_tmp = (unsigned char *) src;
	while (n > 0)
	{
		*dst_tmp = *src_tmp;
		dst_tmp++;
		src_tmp++;
		n--;
	}
	return (dst);
}
