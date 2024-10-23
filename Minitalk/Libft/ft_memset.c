/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:35:57 by nharraqi          #+#    #+#             */
/*   Updated: 2024/05/28 15:55:23 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int val, size_t n)
{
	char	*str;
	size_t	i;

	str = p;
	i = 0;
	while (i < n)
	{
		str[i] = val;
		i++;
	}
	return (p);
}
