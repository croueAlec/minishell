/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:53:34 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 19:04:46 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include "minishell.h"
# include <signal.h>

/* 			SIGNALS			 */
void	sig_handle_c_hd(int signum);
/* 			UTILS			 */
void	set_signals_default(t_env *env);
int		define_sig(int signum, void(*fun_ptr)(int), t_env *env);

#endif
