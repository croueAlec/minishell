/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_question_mark.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:37:38 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/15 11:45:53 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_question_mark_var(char *variable)
{
	if (variable[0] != 63)
		return (0);
	if (variable[1] != '>' && variable[1] != '<' && variable[1] != '$'
		&& variable[1] != ' ' && variable[1] != 0)
		return (0);
	return (1);
}
