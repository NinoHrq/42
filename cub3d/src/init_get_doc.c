/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_get_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:50:51 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/10 15:55:13 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **get_doc(char *filename);
int init_ctx(char *filename, t_doc *ctx);
void	initialize_context(t_doc *ctx, char *filename);
char **allocate_map(int size);
char **reallocate_map(char **map, int pre_size, int new_size);


char **get_doc(char *filename)
{
	t_doc ctx;
	
	if(init_ctx(filename, &ctx) == 1)
		return(NULL);
	ctx.line = get_next_line(ctx.fd);
	while(ctx.line)
	{
		if(ctx.j >= ctx.size - 1)
		{
			ctx.size *= 2;
			ctx.map = reallocate_map(ctx.map, ctx.size/2, ctx.size);
			if (!ctx.map)
			{
				free_tab(ctx.map);
				return (NULL);
			}
		}
		process_line(&ctx);
		ctx.j++;
		free(ctx.line);
		ctx.line = get_next_line(ctx.fd);
	}
	closing_fd(&ctx);
	return(ctx.map);	
}

int init_ctx(char *filename, t_doc *ctx)
{
	initialize_context(ctx, filename);
	if (ctx->fd < 0)
	{
		printf("\n can't open the file in init_ctx \n");
		return (1);
	}
	ctx->map = allocate_map(ctx->size);
	if (!ctx->map)
		return (1);
	return(0);
}

void	initialize_context(t_doc *ctx, char *filename)
{
	ctx->fd = open(filename, O_RDONLY);
	ctx->map = NULL;
	ctx->line = NULL;
	ctx->i = 0;
	ctx->j = 0;
	ctx->size = 8;
}
char **allocate_map(int size)
{
	char **map;
	
	map = malloc(size * sizeof(char *));
	if (!map)
	{
		printf("\n Malloc Failed in allocate_map \n");
		return(NULL);
	}
	return (map);
}

char **reallocate_map(char **map, int pre_size, int new_size)
{
	char **new_map;
	
	new_map = ft_realloc(map, pre_size * sizeof(char *), new_size * sizeof(char*));
	if (!new_map)
	{
		printf("\n Malloc Failed in reallocate_map \n");
		return(NULL);
	}
	return (new_map);
}
