/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:27 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/10 15:32:07 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!old_ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		return (NULL);
	}
	if (old_size < new_size)
	{
		ft_memcpy(new_ptr, old_ptr, old_size);
	}
	else
	{
		ft_memcpy(new_ptr, old_ptr, new_size);
	}
	free(old_ptr);
	return (new_ptr);
}
