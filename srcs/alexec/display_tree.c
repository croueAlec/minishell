/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:51:32 by acroue            #+#    #+#             */
/*   Updated: 2024/03/05 19:13:49 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(char *s)
{
	size_t	len;

	len = ft_strlen(s) + 4;
	write(1, "=========================================================", len);
	printf("\n||%s||\n", s);
	write(1, "=========================================================", len);
	write(1, "\n", 1);
}

void	print_infile_or_outfile(t_type type)
{
	if (type == T_INFILE)
		printf("\n\t  %s", "infile");
	else
		printf("\n\t  %s", "outfilefile");
}

void	print_branches(t_branch *branch)
{
	size_t		len;
	t_infile	*inf;
	t_outfile	*out;
	char		*name;

	name = NULL;
	if (branch->type == T_INFILE)
	{
		inf = branch->elmnt;
		name = inf->path;
	}
	else if (branch->type == T_OUTFILE)
	{
		out = branch->elmnt;
		name = out->path;
	}
	len = ft_strlen(name) + 6;
	write(1, "|\t======================================================", len);
	print_infile_or_outfile(branch->type);
	printf("\n----->\t||%s||\n", name);
	write(1, "|\t======================================================", len);
	write(1, "\n|\n", 3);
}

void	print_end(void)
{
	write(1, "=======\n", 8);
	write(1, "||END||\n", 8);
	write(1, "=======\n", 8);
	write(1, "\n\n", 3);
}

void	differentiate_branches(t_branch *branch)
{
	t_cmd		*cmd;
	size_t		i;

	i = 0;
	cmd = NULL;
	if (branch->type == T_CMD)
	{
		cmd = branch->elmnt;
		print_cmd(cmd->cmd_path);
	}
	while (cmd && cmd->tree[i])
	{
		print_branches(cmd->tree[i]);
		i++;
	}
	print_end();
}
