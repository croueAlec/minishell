/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:57:17 by acroue            #+#    #+#             */
/*   Updated: 2024/04/02 14:06:26 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef enum e_builtin
{
	B_ERR = 0,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_ENV,
	B_CD,
	B_UNSET,
	B_EXIT
}			t_bltin;

# define E_NULL_BUILTIN "The builtin name was NULL\n"
# define E_NO_BUILTIN "does not match any known builtin \
(not supposed to happen)\n"
# define BI_ECHO "echo"
# define BI_PWD "pwd"
# define BI_EXPORT "export"
# define BI_ENV "env"
# define BI_CD "cd"
# define BI_UNSET "unset"
# define BI_EXIT "exit"

int		handle_builtins(t_branch *branch, size_t *cmd_number);

#endif
