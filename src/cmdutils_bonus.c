/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdutils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:12:02 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/17 20:21:08 by kaisuzuk         ###   ########.fr       */
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

t_bool is_builtin(char *cmd)
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
	return (FALSE);
}