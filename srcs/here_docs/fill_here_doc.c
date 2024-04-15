/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:48:30 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 12:11:37 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/**
 * @brief Finds an unused here_doc name.
 * 
 * @return char* The unused here_doc name.
 */
char	*here_doc_name(void)
{
	char	*name;
	char	letter[2];

	letter[0] = 'A';
	letter[1] = '\0';
	name = ft_strdup(HERE_DOC_NAME);
	if (!name)
		return (NULL);
	while (access(name, F_OK) == 0)
	{
		if (ft_safe_strlen(name) >= FILE_NAME_MAX_LEN)
		{
			if (letter[1] == 'Z')
				letter[0] = 'a';
			else if (letter[1] == 'z')
				return (free(name), (void)ft_dprintf(2, E_HERE_DOC_NAME), NULL);
			(free(name), name = NULL);
			name = ft_sep_join(ft_strdup(HERE_DOC_NAME), letter, NULL);
			letter[0]++;
		}
		name = ft_sep_join(name, letter, "");
	}
	return (name);
}

/**
 * @brief Fills the here_doc with readline and expands Vars if needed.
 */
void	fill_here_doc(int write_hd_fd, char *lim, int expand_var, t_env *env)
{
	char	*line;
	size_t	lim_len;

	line = NULL;
	lim_len = (size_t)ft_safe_strlen(lim);
	while (!line || ft_strncmp(line, lim, lim_len + 1) != 0)
	{
		free(line);
		line = readline(HERE_DOC_PROMPT);
		if (!line || ft_strncmp(line, lim, lim_len + 1) == 0)
			break ;
		if (expand_var)
			line = str_expand_var(line, env);
		ft_dprintf(write_hd_fd, "%s\n", line);
	}
	close(write_hd_fd);
	(free(lim), lim = NULL);
}

/**
 * @brief Creates a here_doc file using a here_doc_name(); and fills it with 
 * fill_here_doc(); (This function unlinks the here_doc as soon as it is opened)
 * 
 * @param lim The here_doc's Limiter.
 * @param read_here_doc_fd The here_doc's file descriptor, used in the exec for
 *  reading.
 */
void	create_here_doc(char *lim, int *read_hd_fd, int is_expand, t_env *env)
{
	int		write_here_doc_fd;
	char	*name;

	if (*read_hd_fd != UNDEFINED_FD)
		close(*read_hd_fd);
	name = here_doc_name();
	if (!name)
	{
		*read_hd_fd = E_FD;
		return ;
	}
	write_here_doc_fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (write_here_doc_fd == -1)
		return (perror(name), free(name), free(lim));
	*read_hd_fd = open(name, O_RDONLY);
	if (*read_hd_fd == -1)
	{
		close(write_here_doc_fd);
		return (perror(name), (void)unlink(name), free(name), free(lim));
	}
	if (unlink(name) == -1)
		return (perror(name), free(name), free(lim));
	(free(name), name = NULL);
	fill_here_doc(write_here_doc_fd, lim, is_expand, env);
}
