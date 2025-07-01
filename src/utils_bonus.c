/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:03:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/02 00:16:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 引数がすでにpathかどうかの処理 
static t_bool absolute_program(char *arg)
{
	if (ft_strchr(arg, '/') != NULL)
		return (TRUE);
	return (FALSE);
}

static char *join_path_element(char *dir, char *arg)
{
	char *full_path;
	char *tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL); // どうするかねえ
	full_path = ft_strjoin(tmp, arg);
	free(tmp);
	if (!full_path)
		return (NULL); // うーん
	return (full_path);
}

static char *get_path_line(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *search_for_command(char *arg, char *envp[])
{
	const char *path_line = get_path_line(envp);
	char **path;
	int i;
	char *full_path;
	int res;
	
	if (absolute_program(arg))
		return (arg);
	if (!path_line)
		return (NULL); //エラー処理考えようね
	path = ft_split(path_line, ':');
	if (!path)
		return (NULL); //　どうしようね
	i = 0;
	while (path[i])
	{
		full_path = join_path_element(path[i], arg);
		if (!full_path)
			return (NULL); // なやましい
		res = access(full_path, X_OK);
		if (!res)
		{
			free(path); // これ二次元配列だから開放できてないよ
			return (full_path);
		}
		i++;
	}
	free(path); // ここもね
	return (NULL);
}

//環境変数とクォートで囲まれた文字列のケース
char **make_command(char *arg)
{
	char **cmd;
	
	cmd = ft_split(arg, ' ');
	if (!cmd)
		return (NULL); // エラー処理考えようね
	return (cmd);
}