/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:53:58 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 19:07:40 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	validate_identifier(char *line);
int	parse_doc(char **doc, int start_map);
void	exit_properly_parsing(t_game *game);


int	parse_doc(char **doc, int start_map)
{
	int	i;

	i = 0;
	while (doc[i])
	{
		if (i < start_map)
		{
			if (validate_identifier(doc[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	validate_identifier(char *line)
{
	int	j;

	if (ft_strncmp(line, "NO ", 3) != 0 && ft_strncmp(line, "SO ", 3) != 0
		&& ft_strncmp(line, "WE ", 3) != 0 && ft_strncmp(line, "EA ", 3) != 0
		&& ft_strncmp(line, "F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
	{
		j = 0;
		while (line[j] && line[j] <= 32)
			j++;
		if (line[j] != '\0')
		{
			printf("\n\n\tError: Invalid identifier \"%s\"\n\n\n", line);
			return (1);
		}
	}
	return (0);
}

void	exit_properly_parsing(t_game *game)
{
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->map)
		free_tab(game->map);
	if (game->doc)
		free_tab(game->doc);
	exit(1);
}

