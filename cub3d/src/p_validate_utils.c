/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:26:51 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 23:07:19 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

bool	valid_texture(t_game *game);
void	parse_texture(t_game *game);
bool	ends_with_xpm(char *path);
int	check_texture_path(const char *path);

bool	valid_texture(t_game *game)
{
	if (!ends_with_xpm(game->north_texture)
		|| !ends_with_xpm(game->south_texture)
		|| !ends_with_xpm(game->west_texture)
		|| !ends_with_xpm(game->east_texture))
	{
		printf("\n\n\tError: Invalid texture\n\n\n");
		return (false);
	}
	parse_texture(game);
	if (check_texture_path(game->north_texture)
		|| check_texture_path(game->south_texture)
		|| check_texture_path(game->west_texture)
		|| check_texture_path(game->east_texture))
	{
		printf("\n\n\tError: Invalid texture file\n\n\n");
		return (false);
	}
	return (true);
}

void	parse_texture(t_game *game)
{
	game->north_texture = skip_isspace(game->north_texture);
	game->south_texture = skip_isspace(game->south_texture);
	game->west_texture = skip_isspace(game->west_texture);
	game->east_texture = skip_isspace(game->east_texture);
}

bool	ends_with_xpm(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len > 0)
		len--;
	while (len != 0 && path[len] <= 32)
		len--;
	len++;
	path[len] = '\0';
	if (len < 4)
		return (false);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

int	check_texture_path(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		return (1);
	}
	close(fd);
	return (0);
}

