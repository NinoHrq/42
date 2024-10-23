/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:12:25 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/18 15:09:07 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_argmts(char type, va_list args)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (type == 'p')
		count += ft_ptrhexa(va_arg(args, void *));
	else if (type == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (type == 'u')
		count += ft_putnbru(va_arg(args, unsigned int));
	else if (type == 'd' || type == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (type == 'X')
		count += ft_printhexa_maj(va_arg(args, int));
	else if (type == 'x')
		count += ft_printhexa_min(va_arg(args, int));
	else
		return (-1);
	return (count);
}

static int	ft_print_parkour(const char *str, va_list args)
{
	int	i;
	int	leng;

	i = 0;
	leng = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			return (-1);
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == '%')
				leng += ft_putchar('%');
			else if (ft_strchr("cspdiuxX", str[i]))
				leng += ft_argmts(str[i], args);
		}
		else
			leng += ft_putchar(str[i]);
		i++;
	}
	return (leng);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	if (!str)
		return (-1);
	va_start(args, str);
	len = ft_print_parkour(str, args);
	va_end(args);
	return (len);
}
