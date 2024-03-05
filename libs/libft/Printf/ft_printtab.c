/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:09:56 by jblaye            #+#    #+#             */
/*   Updated: 2024/01/15 10:35:08 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printinttab(int *tab, int len)
{
	if (!tab)
		return ;
	while (len > 0)
	{
		ft_printf("%d\n", *tab);
		len--;
		tab++;
	}
}

void	ft_printstrtab(char **tab)
{
	if (!tab)
		return ;
	while (*tab != 0)
	{
		ft_printf("%s\n", *tab);
		tab++;
	}
}
