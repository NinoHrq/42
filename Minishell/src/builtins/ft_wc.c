#include "../../minishell.h"

/*
		-l : Compte le nombre de lignes
		-w : Compte le nombre de mots
		-c : Compte le nombre de caractères
		-m : Compte le nombre de caractères
		-L : Affiche la longueur de la ligne la plus longue
*/

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	init_wc_struct(t_wc *wc)
{
	wc->chars = 0;
	wc->lines = 0;
	wc->longest_line = 0;
	wc->words = 0;
	wc->current_line_length = 0;
	wc->bytes_read = 0;
	wc->flag_l = 0;
	wc->flag_w = 0;
	wc->flag_c = 0;
	wc->flag_m = 0;
	wc->flag_L = 0;
	wc->j = 0;
}

int	count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep && str[i] != '\0')
			i++;
		if (str[i] != sep && str[i] != '\0')
			count++;
		while (str[i] != sep && str[i] != '\0')
			i++;
	}
	return (count);
}

void	ft_wc(char *input)
{
	t_wc	*wc;
	char	**args;
	int		fd;
	char	buffer[4096];
	int		i;
	char	*line;
	int		check;

	check = 0;
	wc = malloc(sizeof(t_wc));
	init_wc_struct(wc);
	args = ft_split(input, ' ');
	if (args[1] == NULL || ft_strcmp(args[1], "-") == 0)
	{
		line = NULL;
		wc->chars = wc->lines = wc->longest_line = wc->words = wc->current_line_length = 0;
		while ((line = readline("")))
		{
			wc->lines++;
			wc->chars += ft_strlen(line) + 1;
			wc->words += count_words(line, ' ');
			if (ft_strlen(line) > (unsigned long)wc->longest_line)
				wc->longest_line = ft_strlen(line);
			free(line);
		}
		ft_printf("\t%d\t%d\t%d\n", wc->lines, wc->words, wc->chars);
		check = 1;
	}
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			wc->j = 1;
			while (args[i][wc->j] != '\0')
			{
				if (args[i][wc->j] == 'l')
					wc->flag_l = 1;
				else if (args[i][wc->j] == 'w')
					wc->flag_w = 1;
				else if (args[i][wc->j] == 'c')
					wc->flag_c = 1;
				else if (args[i][wc->j] == 'm')
					wc->flag_m = 1;
				else if (args[i][wc->j] == 'L')
					wc->flag_L = 1;
				else
				{
					ft_printf("💥_(╬ಠ益ಠ)_💥: invalid option -- '%c'\n",
						args[i][wc->j]);
					free_split(args);
					free(wc);
					return ;
				}
				wc->j++;
			}
		}
		i++;
	}
	i = 1;
	if (args[i] == NULL && check == 0)
	{
		ft_printf("💥_(╬ಠ益ಠ)_💥: usage: wc <option> <filename>\n");
		free_split(args);
		free(wc);
		return ;
	}
	while (args[i] != NULL)
	{
		if (args[i][0] == '-')
		{
			i++;
			continue ;
		}
		fd = open(args[i], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("💥_(╬ಠ益ಠ)_💥: %s: No such file or directory\n", args[i]);
			i++;
			continue ;
		}
		wc->chars = wc->lines = wc->longest_line = wc->words = wc->current_line_length = 0;
		while ((wc->bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[wc->bytes_read] = '\0';
			wc->j = 0;
			while (wc->j < wc->bytes_read)
			{
				wc->chars++;
				if (buffer[wc->j] == '\n')
				{
					wc->lines++;
					if (wc->current_line_length > wc->longest_line)
						wc->longest_line = wc->current_line_length;
					wc->current_line_length = 0;
				}
				else
					wc->current_line_length++;
				if ((wc->j == 0 || ft_isspace(buffer[wc->j - 1]))
					&& !ft_isspace(buffer[wc->j]))
					wc->words++;
				wc->j++;
			}
		}
		close(fd);
		if (wc->flag_l)
			ft_printf("%d ", wc->lines);
		if (wc->flag_w)
			ft_printf("%d ", wc->words);
		if (wc->flag_c || wc->flag_m)
			ft_printf("%d ", wc->chars);
		if (wc->flag_L)
			ft_printf("%d ", wc->longest_line);
		if (!wc->flag_l && !wc->flag_w && !wc->flag_c && !wc->flag_m
			&& !wc->flag_L)
			ft_printf("\t%d\t%d\t%d %s\n", wc->lines, wc->words, wc->chars,
				args[i]);
		else
			ft_printf("%s\n", args[i]);
		i++;
	}
	free_split(args);
	free(wc);
}
