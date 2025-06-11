/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:55:42 by marvin            #+#    #+#             */
/*   Updated: 2025/06/11 19:21:52 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void parsing_configuration(t_game *game, char **doc);
void init_parser_context(t_parser_context *ctx);


void parsing_configuration(t_game *game, char **doc)
{
    t_parser_context ctx;

    init_parser_context(&ctx);
    parse_textures(game, doc, &ctx);

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
    while (doc[ctx->i])
}