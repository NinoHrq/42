/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:37:27 by tmilin            #+#    #+#             */
/*   Updated: 2025/01/16 12:55:30 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*res;

	cc = (char) c;
	res = NULL;
	while (*s != '\0')
	{
		if (*s == cc)
			res = ((char *) s);
		s++;
	}
	if (cc == '\0')
		res = ((char *) s);
	return (res);
}
