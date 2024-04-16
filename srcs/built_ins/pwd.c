/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:03:17 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/16 21:22:06 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_built_in(int fd_out)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (pwd == NULL)
		strerror(errno);
	else
	{
		if (write(fd_out, pwd, ft_strlen(pwd)) < 0)
			return ((void)ft_dprintf(2, WRITE_FILE_FULL, "echo"), free(pwd), 1);
		if (write(fd_out, "\n", 1) < 0)
			return ((void)ft_dprintf(2, WRITE_FILE_FULL, "echo"), free(pwd), 1);
	}
	free(pwd);
	return (errno);
}
