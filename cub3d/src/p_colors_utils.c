/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_colors_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:46:07 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 18:38:09 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

long my_strtol(const char *str, char **endptr, int base);
void	skip_whitespace(const char **str):
int	get_sign(const char **str);
int	determine_base(const char **str, int base);
long	parse_digits(const char **str, int base, int sign, char **endptr);

long my_strtol(const char *str, char **endptr, int base)
{
	int	sign;

	skip_whitespace(&str);
	sign = get_sign(&str);
	base = determine_base(&str, base);
	return (parse_digits(&str, base, sign, endptr));
}

void	skip_whitespace(const char **str)
{
	while (isspace((unsigned char)**str))
		(*str)++;
}

int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

int	determine_base(const char **str, int base)
{
	if ((base == 0 || base == 16) && **str == '0' && ((*str)[1] == 'x'
		|| (*str)[1] == 'X'))
	{
		base = 16;
		(*str) += 2;
	}
	else if (base == 0 && **str == '0')
	{
		base = 8;
		(*str)++;
	}
	else if (base == 0)
		base = 10;
	return (base);
}
long	parse_digits(const char **str, int base, int sign, char **endptr)
{
	t_parse_state	state;

	state.result = 0;
	while (**str)
	{
		state.digit = get_digit_value(**str);
		if (state.digit == -1 || !is_valid_digit(state.digit, base))
			break ;
		state.result = update_result(&state, base, sign, endptr);
		(*str)++;
	}
	if (endptr)
		*endptr = (char *)*str;
	return (state.result * sign);
}
