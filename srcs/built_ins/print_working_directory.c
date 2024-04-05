/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:57:14 by acroue            #+#    #+#             */
/*   Updated: 2024/04/05 16:21:26 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_working_directory(int fd_out, char **env)
{
	char	*curr_dir;

	curr_dir = get_true_current_dir(env);
	if (!curr_dir)
		return (-1);
	ft_dprintf(fd_out, "%s\n", curr_dir);
	free(curr_dir);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	print_working_directory(1, env);
	(void)argc;
	(void)argv;
	return (0);
}
