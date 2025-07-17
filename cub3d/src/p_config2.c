/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_config2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 01:23:52 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 01:38:49 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	find_map_start(char **doc, int i);
int	found_end_of_the_map(char **doc);
int	tablen(char **tab);
int	calculate_map_size(char **doc, int start_map, int end_map);
int	no_empty_line(char **doc, int i, int is_map);

int	find_map_start(char **doc, int i)
{
	while (doc[i] && !ft_strchr(doc[i], '1') && !ft_strchr(doc[i], '0'))
		i++;
	return (i);
}

int	found_end_of_the_map(char **doc)
{
	int	i;
	int	j;

	i = tablen(doc) - 1;
	while (i >= 0)
	{
		j = 0;
		while (doc[i][j] && doc[i][j] <= 32)
			j++;
		if (doc[i][j] != '\0')
			return (i);
		i--;
	}
	return (i);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	calculate_map_size(char **doc, int start_map, int end_map)
{
	int	map_size;
	int	is_map;
	int	temp_i;

	map_size = 0;
	is_map = 0;
	temp_i = start_map;
	while (doc[temp_i])
	{
		if (no_empty_line(doc, temp_i, 1))
		{
			if (!is_map && (ft_strchr(doc[temp_i], '1')
					|| ft_strchr(doc[temp_i], '0')))
				is_map = 1;
			if (is_map)
				map_size++;
		}
		if (temp_i == end_map)
			break ;
		temp_i++;
	}
	return (map_size);
}

int	no_empty_line(char **doc, int i, int is_map)
{
	int	j;

	j = 0;
	while (doc[i][j] && doc[i][j] <= 32)
		j++;
	if (is_map)
		return (1);
	else
		return (doc[i][j] != '\0');
}
