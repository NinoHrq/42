/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:19:36 by tmilin            #+#    #+#             */
/*   Updated: 2024/05/30 15:21:35 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_local(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	*ft_memcpy_local(void *ds, const void *sr, size_t len)
{
	unsigned char	*ds_tmp;
	unsigned char	*sr_tmp;

	if (ds == NULL || sr == NULL)
		return (ds);
	ds_tmp = (unsigned char *) ds;
	sr_tmp = (unsigned char *) sr;
	while (len > 0)
	{
		*ds_tmp = *sr_tmp;
		ds_tmp++;
		sr_tmp++;
		len--;
	}
	return (ds);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;

	src_size = ft_strlen_local(src);
	if (src_size + 1 < dstsize)
		ft_memcpy_local(dst, src, src_size + 1);
	else if (dstsize != 0)
	{
		ft_memcpy_local(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_size);
}
