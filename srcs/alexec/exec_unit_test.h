/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:29 by acroue            #+#    #+#             */
/*   Updated: 2024/03/08 17:11:00 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UNIT_TEST_H
# define EXEC_UNIT_TEST_H

# include "minishell.h"

# define TEST_ERR "./a.out /usr/bin/cat cat -n <in1> <in2> <out1> <out2>\n"
# define TEST_ERR_2 "./a.out /usr/bin/cat cat -n <in1> <in2> <out1> <out2> \
/usr/bin/head head -n3 <in1> <in2> <out1> <out2>\n"

void		define_test_pipe(t_cmd *cmd, char **args);
t_branch	*define_test_infile(char *path);
t_branch	*define_test_outifle(char *path, t_out_type type);
t_branch	*define_test_cmd(t_branch *branch, char **args);

#endif
