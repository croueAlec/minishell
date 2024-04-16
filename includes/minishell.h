/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:14:34 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 18:32:25 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "struct.h"
# include "../libs/libft/libft.h"
# include "redirections.h"
# include "exec.h"
# include <errno.h>
# include <sys/wait.h>
# include "parsing.h"
# include "parsing_struct.h"
# include "builtins.h"
# include "here_doc.h"
# include "minishell_signals.h"

extern int	g_global;

void	print_parsing(void);
void	print_exec(void);
int		is_line_empty(char	*str);

#endif
