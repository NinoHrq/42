/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:05 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/03 18:16:23 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	parse_av(char *filename)
{
	char 	*extension;
	
	verif_name(filename);
	extension = extracting_extension(filename);
	return(verif_extension(extension));
}

void verif_name(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (i == 0)
				exit(1);
			else if (s[i - 1] == '/')
				exit(1);
		}
		i++;
	}
}


char *extracting_extension(char *s)
{
    int i = 0;
    int last_dot = -1;
    int len;
    char *ext;

    if (!s)
        return (NULL);
    while (s[i])
    {
        if (s[i] == '.')
            last_dot = i;
        i++;
    }
    if (last_dot == -1)
        return (NULL);
    len = strlen(s + last_dot);
    ext = malloc(len + 1);
    if (!ext)
        return (NULL);
    strcpy(ext, s + last_dot);

    return (ext);
}

int verif_extension(char *ext)
{
	int	res;

	if (!ext)
		return(0);
	res = ft_strcmp(ext, ".cub");
	free(ext);
	return (res == 1);
	
}
