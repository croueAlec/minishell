#include "minishell.h"

void	set_branch(t_type type, t_branch *branch)
{
	void	*elmnt;
	
	branch->type = type
	if (branch->type == T_CMD)
	{
		elmnt = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
		branch->elmnt = elmnt;
	}	
}

char	*fetch_cmd_path(char *cmd_str)
{

}

t_branch	input_tree(char **input)
{
	t_branch	*first;
	void		*ptr;

	first = (t_branch *) ft_calloc (1, sizeof(t_branch));
	set_branch(T_CMD, first);
	first->elmnt->cmd_path = fetch_cmd_path(input[0]);
}