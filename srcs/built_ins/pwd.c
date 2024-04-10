/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:03:17 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/10 13:52:57 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_built_in(void)
{
	char	*to_be_freed;
	
	to_be_freed = getcwd(0, 0);
	if (to_be_freed == NULL)
		strerror(errno);
	else
		printf("%s\n", to_be_freed);
	free(to_be_freed);
	return (errno);
}
