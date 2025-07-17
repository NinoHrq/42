/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:55:42 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 01:42:00 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void parsing_configuration(t_game *game, char **doc);
void init_parser_context(t_parser_context *ctx);
void parse_textures(t_game *game, char **doc, t_parser_context *ctx);
void	validate_textures(t_game *game, int x);
void	allocate_map(t_game *game, char **doc, int start_map, int map_size);

void parsing_configuration(t_game *game, char **doc)
{
    t_parser_context ctx;

    init_parser_context(&ctx);
    parse_textures(game, doc, &ctx);
    validate_textures(game, ctx.x);
    ctx.start_map = find_map_start(doc, ctx.i);
    ctx.end_map = found_end_map(doc);
    if (doc[ctx.start_map] == NULL)
		free_game_texture(game,
			"\n\n\tError: Not seeing any map here\n\n\n");
	ctx.map_size = calculate_map_size(doc, ctx.start_map, ctx.end_map);
	allocate_map(game, doc, ctx.start_map, ctx.map_size);
	game->start_map = ctx.start_map;

}

void init_parser_context(t_parser_context *ctx)
{
	ctx->i = 0;
    ctx->j = 0;
    ctx->x = 0;
    ctx->start_map = 0;
	ctx->end_map = 0;
	ctx->map_size = 0;
}

void parse_textures(t_game *game, char **doc, t_parser_context *ctx)
{
    while (doc[ctx->i] && ctx->j < 6)
    {
        doc[ctx->i] = parse_doc_line(doc[ctx->i]);
        if (ft_strncmp(doc[ctx->i], "NO ", 3) == 0 || ft_strncmp(doc[ctx->i],
				"SO ", 3) == 0 || ft_strncmp(doc[ctx->i], "WE ", 3) == 0
			|| ft_strncmp(doc[ctx->i], "EA ", 3) == 0)
        {
            handle_texture_directive(game, ctx, doc[ctx->i]);
            ctx->j++;
            ctx->i++;
        }
        else if (ft_strncmp(doc[ctx->i], "F ", 2) == 0 
            || ft_strncmp(doc[ctx->i], "C ", 2) == 0)
            {
                handle_color_directive(game, ctx, doc[ctx->i]);
                ctx->j++;
                ctx->i++;
            }
            else
                ctx->i++;
    }
}

void	validate_textures(t_game *game, int x)
{
	if (x != 6)
		free_game_texture(game,
			"\n\n\tError: Miss Identifier Texture\n\n\n");
	if (game->north_texture == NULL)
		free_game_texture(game,
			"\n\n\tError: Miss North Texture\n\n\n");
	if (game->south_texture == NULL)
		free_game_texture(game,
			"\n\n\tError: Miss South Texture\n\n\n");
	if (game->west_texture == NULL)
		free_game_texture(game,
			"\n\n\tError: Miss West Texture\n\n\n");
	if (game->east_texture == NULL)
		free_game_texture(game,
			"\n\n\tError: Miss East Texture\n\n\n");
	if (valid_texture(game) == false)
		free_game_texture(game, "");
}

void	allocate_map(t_game *game, char **doc, int start_map, int map_size)
{
	int	i;
	int	j;

	game->map = malloc(sizeof(char *) * (map_size + 1));
	if (!game->map)
		return ;
	j = 0;
	i = start_map;
	while (doc[i] && j < map_size)
	{
		game->map[j] = ft_strdup(doc[i]);
		if (!game->map[j])
		{
			while (--j >= 0)
				free(game->map[j]);
			free(game->map);
			game->map = NULL;
			return ;
		}
		j++;
		i++;
	}
	game->map[j] = NULL;
}
