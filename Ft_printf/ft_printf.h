/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:34:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/11 12:27:12 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);

// fonctions
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int n);
int		ft_putnbr_base(unsigned long nbr, char *base);
int		ft_printhexa_maj(unsigned int c);
int		ft_printhexa_min(unsigned int c);
int		ft_ptrhexa(void *ptr);
int		ft_putnbru(unsigned int n);
char	*ft_strchr(const char *s, int c);

#endif
