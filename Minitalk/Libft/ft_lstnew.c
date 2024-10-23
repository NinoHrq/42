/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:17:56 by nharraqi          #+#    #+#             */
/*   Updated: 2024/05/28 18:00:59 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elemt;

	elemt = malloc(sizeof(t_list));
	if (!elemt)
		return (NULL);
	elemt->content = content;
	elemt->next = NULL;
	return (elemt);
}
