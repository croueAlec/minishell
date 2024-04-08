/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:39:01 by acroue            #+#    #+#             */
/*   Updated: 2024/04/08 17:09:59 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_exist(char **env, char *arg, size_t *var_exist)
{
	size_t	key_length;
	size_t	i;

	key_length = length_until_char(arg, '=');
	*var_exist = 0;
	i = 0;
	while (*var_exist == 0 && env && env[i])
	{
		if (ft_strncmp(env[i], arg, key_length) == 0)
			*var_exist = 1;
		i++;
	}
	if (*var_exist)
		return (0);
	return (1);
}

char	**replace_in_env(char **env, char *arg)
{
	size_t	i;
	size_t	key_length;

	key_length = length_until_char(arg, '=');
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], arg, key_length) != 0)
		i++;
	free(env[i]);
	env[i] = arg;
	return (env);
}

char	**add_to_env(char **env, char *arg)
{
	char	**new_env;
	size_t	i;
	size_t	var_exist;

	i = tab_len(env) + check_var_exist(env, arg, &var_exist);
	if (var_exist)
		return (replace_in_env(env, arg));
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[i] = NULL;
	i = 0;
	while (env && env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = arg;
	free(env);
	return (new_env);
}

int	export_built_in(t_branch *br, int fd_out)
{
	t_cmd	*cmd;
	size_t	i;
	int		err_no;

	i = 0;
	err_no = 0;
	cmd = br->elmnt;
	if (cmd && cmd->args && !cmd->args[1])
		return (export_print_env(cmd, fd_out));
	while (cmd && cmd->args && cmd->args[i])
	{
		if (is_valid_env_var(cmd->args[i]))
			cmd->env->env_tab = add_to_env(cmd->env->env_tab, cmd->args[i]);
		else
			err_no = 1;
		i++;
	}
	return (err_no);
}

int	main(int argc, char *argv[])
{
	char		*test[5] = {"salut", "bjr", "cc", "hello", 0};
	t_branch	*br;
	t_cmd		*cmd;
	t_env		*env;
	int			err;

	env = ft_calloc(1, sizeof(t_env));
	cmd = ft_calloc(1, sizeof(t_cmd));
	br = ft_calloc(1, sizeof(t_branch));
	env->env_tab = test;
	cmd->env = env;
	cmd->args = argv;
	br->elmnt = cmd;
	err = export_built_in(br, 1);
	(void)argc;
	return (free(cmd), free(br), free(env), err);
}
