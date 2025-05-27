/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:24:00 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/08 12:43:38 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ee	*ee;
	int		status;
	char	*input;

	status = 0;
	ee = malloc(sizeof(t_ee));
	input = NULL;
	(void)ac;
	(void)av;
	init_struct(ee);
	ee->envp = copy_envp(envp);
	ee->save_initial_path = save_initial_path(ee);
	ee->copy_home = save_initial_home(ee);
	catch_signal(ee);
	while (ee->minishell_check == 0)
		loop(input, ee);
	if (ee->code_exit != 0)
		status = ee->code_exit;
	all_is__freed(ee);
	clear_history();
	exit(status);
	return (0);
}

/*

echo "cat << e |wc -l | ls > lol || pwd < Makefile | ./minishell" >> ls

cat Makefile | wc -l && (pwd && ls && cat Makefile | lol|| cat <<e > lol && kek
	&& (lol)) && ls
	
ls && pwd && koke || ls && (ls && (cat Makefile |wc -l && (ppp || w )&& kwk)
	&& ls) || echo fini
	
cat << e << o << f> lol

cat Makefile | wc -l && (pwd && ls && cat Makefile | lol|| cat <<e > lol ) && ls

(cat Makefile | wc -l && cat Makefile|wc -l && (cat << e > lol || kek))	&& pwd

ls && (lol || "$qwer")
	|| pwd                                                                  */