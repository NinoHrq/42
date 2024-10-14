/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:39 by nharraqi          #+#    #+#             */
/*   Updated: 2024/10/14 16:56:31 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# define SIZE 150000

// server.c
void	handle_signal(int sig);
/*void	fill_buff(char c);
void	buffer_printnclear(void);*/

// client.c
//void	send_onebit(int pid, char bit);
void	send_char(int pid, char c);
//void	send_all(int pid, const char *message);

#endif