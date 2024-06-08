/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:56:29 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/08 17:27:36 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	char	i;

	i = c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && i == '\0')
		return ((char *)s);
	return (NULL);
}
