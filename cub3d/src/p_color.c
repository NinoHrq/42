/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:58:57 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 19:13:12 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	handle_color_directive(t_game *game, t_parser_context *ctx, char *line);
void parse_color(char *s,  int color[3], t_game *game);
int	parse_color_line(char *s);


void	handle_color_directive(t_game *game, t_parser_context *ctx, char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
    {
        parse_color(line + 2, game->floor_color, game);
        if (parsed_color_line(line))
            free_game_texture(game, "\n\n\tError: Wrong floor format\n\n\n");
        check_color(game->floor_color, game);
        ctx->x++;
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        parse_color(line + 2 , data->ceiling_color, game);
        if (parse_color_line(line))
            free_game_texture(game, "\n\n\tError: Wrong ceiling format\n\n\n");
        check_color(game->ceiling_color, game);
        ctx->x++;
    }
}
void parse_color(char *s,  int color[3], t_game *game)
{
    char *ptr;
    char *end;
    int i;

    ptr = s;
    i = 0;
    while (i < 3)
    {
        color[i] = my_strtol(ptr, &end, 10);
        if(ptr == end || color[i] < 0 || color[i] > 255)
        {
            printf("\n\n\tError: Invalid color format\n\n\n");
            free_wrong_color(game);
        }
        ptr = end;
        if (i < 2)
            protect_wrong_color(&ptr, game);
        i++;
    }
}

int	parse_color_line(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] <= 32)
		i++;
	if (s[i] == '\0')
		return (1);
	while (s[i] && s[i] > 32)
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ',')
			return (1);
		i++;
	}
	while (s[i] && s[i] <= 32)
		i++;
	if (s[i] != '\0')
		return (1);
	return (0);
}

void	check_color(int tab[3], t_game *game)
{
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
	{
		printf("\n\n\tError: Invalid color format\n\n\n");
		free_wrong_color(game);
	}
}