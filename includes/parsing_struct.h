/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:40:08 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/04 13:54:53 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCT_H
# define PARSING_STRUCT_H

typedef enum e_pars_type
{
	PARS_ARG = 1,
	PARS_IN = 2,
	PARS_HERE_DOC = 3,
	PARS_TRUNC_OUT = 4,
	PARS_APP_OUT = 5,
	PARS_CMD = 6
}			t_pars_type;

typedef struct s_pars_list
{
	t_pars_type			type;
	char				*s;
	struct s_pars_list	*next;
}				t_pars_list;

typedef struct s_hd_fd_list
{
	int					fd;
	struct s_hd_fd_list	*next;
}				t_hd_fd_list;

#endif