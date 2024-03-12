#include "minishell.h"

int	in_outfile_len(char *str)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = 0;
	if (str[i] == 60 || str[i] == 62)
	{
		i++;
		while (str[i] == ' ')
			i++;
		while (str[len + i] != 0 && str[len + i] != ' '
			&& str[len + i] != 60 && str[len + i] != 62)
		{
			if (str[len + i] == '\"' || str[len + i] == '\'')
			{
			quote = str[len + i];
			len++;
			while (str[len + i] != quote && str[len + i] != 0)
				len++;
			}
			len++;
		}
	}
	return (len);
}
