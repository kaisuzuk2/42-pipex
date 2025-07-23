/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdutils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:12:02 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/23 16:21:02 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	if (!ft_strcmp(cmd, "cd"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "export"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "unset"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "exit"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "."))
		return (TRUE);
	return (FALSE);
}
