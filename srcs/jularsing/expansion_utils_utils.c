/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:33:55 by acroue            #+#    #+#             */
/*   Updated: 2024/04/16 23:34:26 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_forward_single_quotes(size_t *len, char *str)
{
	len[EXP_LEN] += 2;
	while (str[len[LEN]] != '\'')
	{
		len[EXP_LEN] += 1;
		len[LEN] += 1;
	}
	len[LEN] += 1;
}
