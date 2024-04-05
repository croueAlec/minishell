/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:59:48 by acroue            #+#    #+#             */
/*   Updated: 2024/04/05 15:49:28 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_only_n(char *str, char ch)
{
	size_t	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != ch)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief This function returns the first str that needs to be printed and sets 
 * print_newline to 1 if the [-n] flag was present.
 */
static char	**skip_n_flag(t_cmd *cmd, int *print_newline)
{
	size_t	i;
	char	**args;

	i = 1;
	*print_newline = 1;
	args = cmd->args;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n' && str_only_n(args[i], 'n'))
			*print_newline = 0;
		else
			break ;
		i++;
	}
	return (&args[i]);
}

void	echo_built_in(t_branch *branch, int fd_out)
{
	char	**args;
	int		print_newline;
	size_t	i;

	i = 0;
	args = skip_n_flag(branch->elmnt, &print_newline);
	while (args[i])
	{
		write(fd_out, " ", (i > 0));
		ft_putstr_fd(args[i], fd_out);
		i++;
	}
	write(fd_out, "\n", print_newline);
}

/* int	main(int argc, char *argv[])
{
	t_branch	*br;
	t_cmd		*cmd;

	br = ft_calloc(1, sizeof(t_branch));
	cmd = ft_calloc(1, sizeof(t_cmd));
	br->elmnt = cmd;
	cmd->args = argv;
	echo_built_in(br, 1);
	free(cmd);
	free(br);
	(void)argc;
	return (0);
} */

