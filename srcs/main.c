/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:13:47 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 15:54:10 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	printf("This is a test\n");
	print_exec();
	print_parsing();
	return (0);
}
