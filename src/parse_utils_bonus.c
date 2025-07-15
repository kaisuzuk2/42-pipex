/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:50:43 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/15 19:52:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	is_here_doc(char *cmd)
{
	return (ft_strcmp(cmd, "here_doc") == 0);
}

t_bool	args_check(int argc, char **argv)
{
	if (argc < MIN_ARG)
		return (FALSE);
	if (is_here_doc(argv[1]) && argc < MIN_HEREDOC_ARG)
		return (FALSE);
	return (TRUE);
}