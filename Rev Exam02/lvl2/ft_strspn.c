#include <string.h>

size_t ft_strcpn(const char *s, const char *accept)
{
	int i;
	int j;
	size_t check;

	i = 0;
	check = 0;
	while(s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				check = 1;
			j++;			
		}
		if (check == 0)
		{
			return (i);
		}
		i++;		
	}
	return (i);
}
