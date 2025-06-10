/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_get_doc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:36:35 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/10 16:28:17 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void process_line(t_doc *ctx);
void cleaning_up(t_doc *ctx);
void closing_fd(t_doc *ctx);

void process_line(t_doc *ctx)
{
	ctx->i = 0;
	while (ctx->line[ctx->i] != '\n' && ctx->line[ctx->i] != '\0')
		ctx->i++;
	if(ctx->line[ctx->i] == '\n')
		ctx->line[ctx->i] == '\0';
	ctx->map[ctx->j] = ft_strdup(ctx->line);
	if(!ctx->map[ctx->j])
	{
		printf("\n Memory allocation failed in process_line \n");
		cleaning_up(ctx);
		exit(EXIT_FAILURE);
	}
}	

void cleaning_up(t_doc *ctx)
{
	int k;
	
	k = 0;
	while (k < ctx->j)
	{
		free(ctx->map[k]);
		k++;
	}
	free(ctx->j);
	close(ctx->fd);
}

void closing_fd(t_doc *ctx)
{
	ctx->map[ctx->j] = NULL;
	close(ctx->fd);
}
