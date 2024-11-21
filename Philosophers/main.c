/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:05:54 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 20:45:27 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table table;
    
    if (ac == 5 || ac == 6)
    {
        parse_input(&table, av);
        data_init(&table);
        start_dinner(&table);
        clean(&table);
    }
    else
    {
       error_quit("Wrong input:\n"
            GREEN"Example of usage : ./philo 5 800 200 200 [5](optional)\n"RST);
    }
}