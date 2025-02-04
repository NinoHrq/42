/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:35:40 by tmilin            #+#    #+#             */
/*   Updated: 2024/05/30 15:37:13 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *nd, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (nd[0] == '\0')
		return ((char *) hs);
	while (hs[i] && i < len)
	{
		while (hs[i + j] == nd[j] && hs[i + j] && i + j < len)
		{
			j++;
			if (nd[j] == 0)
				return ((char *) hs + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
