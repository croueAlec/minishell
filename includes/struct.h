/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:43:39 by acroue            #+#    #+#             */
/*   Updated: 2024/03/07 14:12:16 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define HEREDOC_TEST_PATH "/home/acroue/Documents/42cursus/test_minishell/u/hd"

# define UNDEFINED_FD -2
# define E_FD -1

/*		====		ENUMS		====		*/
typedef enum e_type
{
	T_CMD = 1,
	T_INFILE,
	T_OUTFILE
}			t_type;

typedef enum e_outile_type
{
	OT_TRUNC = 1,
	OT_APPEND
}			t_out_type;

typedef enum e_infile_type
{
	IT_RDONLY = 1,
	IT_HERE_DOC
}			t_int_type;

/*		====		STRUCTS		====		*/
typedef struct s_infile
{
	t_int_type	type;
	char		*path;
}				t_infile;

typedef struct s_outfile
{
	t_out_type	type;
	char		*path;
}				t_outfile;

typedef struct s_branch
{
	t_type	type;
	void	*elmnt;
}			t_branch;

typedef struct s_cmd
{
	char		*cmd_path;
	char		**args;
	t_branch	*next_cmd;
	t_branch	**tree;
}			t_cmd;

#endif
