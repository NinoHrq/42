/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_colors_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:30:59 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 18:48:30 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	get_digit_value(char c);
int	is_valid_digit(int digit, int base);
long	update_result(t_parse_state *state, int base, int sign, char **endptr);
void	free_wrong_color(t_game *game);
void	protect_wrong_color(char **ptr, t_game *game);

int	get_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

int	is_valid_digit(int digit, int base)
{
	return (digit >= 0 && digit < base);
}

long	update_result(t_parse_state *state, int base, int sign, char **endptr)
{
	if (state->result > (LONG_MAX - state->digit) / base)
	{
		if (sign == 1)
			state->result = LONG_MAX;
		else
			state->result = LONG_MIN;
		if (endptr)
			*endptr = (char *)*endptr;
		return (state->result);
	}
	return (state->result * base + state->digit);
}

void	free_wrong_color(t_game *game)
{
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

void	protect_wrong_color(char **ptr, t_game *game)
{
	if (**ptr != ',')
	{
		printf("\n\n\tError: Invalid color format\n\n\n");
		free_wrong_color(game);
	}
	(*ptr)++;
}