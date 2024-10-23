char *ft_strrev(char *str)
{
	int i;
	int len;
	char tmp;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (str[i])
	{
		while(i < len / 2)
		{
			tmp = str[i];
			str[i] = str[len - 1 -i];
			str[len - 1 - i] = tmp;
		}
		i++;
	}
	return(str);
}