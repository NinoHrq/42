/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:29 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 15:46:23 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	assign_texture(t_game *game, t_parser_context *ctx, char c, char *doc);
void	assign_north_texture(t_game *game, char *doc);
void	assign_south_texture(t_game *game, char *doc);
void	assign_west_texture(t_game *game, char *doc);
void	assign_east_texture(t_game *game, char *doc);

void	assign_north_texture(t_game *game, char *doc)
{
	if (!game->north_texture)
		game->north_texture = ft_strdup(doc + 3);
	else
		free_game_texture(game,
			"\n\n\tError : dupplicate texture (NO)\n\n\n");
}

void	assign_south_texture(t_game *game, char *doc)
{
	if (!game->south_texture)
		game->south_texture = ft_strdup(doc + 3);
	else
		free_game_texture(game,
			"\n\n\tError : duplicate texture (SO)\n\n\n");
}

void	assign_west_texture(t_game *game, char *doc)
{
	if (!game->west_texture)
		game->west_texture = ft_strdup(doc + 3);
	else
		free_game_texture(game,
			"\n\n\tError : dupplicate texture (WE)\n\n\n");
}

void	assign_east_texture(t_game *game, char *doc)
{
	if (!game->east_texture)
		game->east_texture = ft_strdup(doc + 3);
	else
		free_game_texture(game,
			"\n\n\tError : dupplicate texture (EA)\n\n\n");
}

void	assign_texture(t_game *game, t_parser_context *ctx, char c, char *doc)
{
	if (!doc[3])
		return ;
	if (c == 'N')
		assign_north_texture(game, doc);
	else if (c == 'S')
		assign_south_texture(game, doc);
	else if (c == 'W')
		assign_west_texture(game, doc);
	else if (c == 'E')
		assign_east_texture(game, doc);
	ctx->x++;
}
