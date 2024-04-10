/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:57:17 by acroue            #+#    #+#             */
/*   Updated: 2024/04/10 17:52:08 by acroue           ###   ########.fr       */
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
# define WRITE_FILE_FULL "tacOS: %s: write error: No space left on device\n"
# define ENV_WRITE_FULL "%s: write error: No space left on device\n"
# define EXPORT_MALLOC_FAIL "tacOS: %s: Malloc failed, environnment was \
not changed\n"

/* 			ECHO			 */
int		echo_built_in(t_branch *branch, int fd_out);
/* 			PWD				 */
int		pwd_built_in(int fd_out);
/* 			ENV				 */
int		env_built_in(t_cmd *cmd, int fd_out);
/* 			UNSET			 */
char	**remove_from_env(char **env, char *var);
int		unset_built_in(t_branch *branch);
/* 			EXPORT			 */
char	**add_to_env(char **env, char *arg, int *err_no);
int		is_valid_env_var(const char *s);
size_t	length_until_char(const char *str, char ch);
int		export_print_env(t_cmd *cmd, int fd_out);
int		export_built_in(t_branch *br, int fd_out);
/* 			ENV UTILS		 */
t_env	*make_env(char **env_tab);
size_t	tab_len(char **tab);
char	**sort_char_tab(char **tab);
size_t	length_until_char(const char *str, char ch);
/* 			BUILTINS UTILS	 */
pid_t	fork_built_ins(int	fd_out, t_branch *branch, size_t *cmd_number);
int		is_built_in(t_branch *branch);
int		handle_builtins(t_branch *branch, size_t *cmd_number, int outfile);

#endif
