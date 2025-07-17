/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_config_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:06:22 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 01:44:07 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

char	*parse_doc_line(char *s);
void	handle_texture_directive(t_game *game, t_parser_context *ctx,
		char *line);
void	free_game_texture(tgame game, char *msg);

char	*parse_doc_line(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tmp)
		return (s);
	while (s[i] && s[i] <= 32)
		i++;
	while (s[i])
	{
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(s);
	return (tmp);
}

void	handle_texture_directive(t_game *game, t_parser_context *ctx,
		char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		assign_texture(game, ctx, 'N', line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		assign_texture(game, ctx, 'S', line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		assign_texture(game, ctx, 'W', line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		assign_texture(game, ctx, 'E', line);
}

void	free_game_texture(t_game *game, char *msg)
{
	printf("%s", msg);
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->doc)
		free_tab(game->doc);
	exit(1);
}
