/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdutils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:12:02 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/04 22:23:54 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//環境変数とクォートで囲まれた文字列のケース
char **make_command(char *arg)
{
	char **cmd;

	cmd = ft_split(arg, ' ');
	return (cmd);
}

// strcmp作ろうね
t_bool is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2))
		return (TRUE);
	else if (!ft_strncmp(cmd, "export", 6))
		return (TRUE);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (TRUE);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (TRUE);
	return (FALSE);
}