/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:48:59 by acroue            #+#    #+#             */
/*   Updated: 2024/03/25 13:23:31 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"

# ifndef HERE_DOC_PROMPT
#  define HERE_DOC_PROMPT "hd> "
# endif
# ifndef HERE_DOC_NAME
#  define HERE_DOC_NAME ".here_doc"
# endif
# ifndef FILE_NAME_MAX_LEN
#  define FILE_NAME_MAX_LEN 255
# endif
# define E_HERE_DOC_NAME "No suitable here_doc name found"

int		find_lim(char *cmd, size_t *i, char **lim);
void	create_here_doc(char *lim, int *read_here_doc_fd);

#endif
