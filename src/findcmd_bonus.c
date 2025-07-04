/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:03:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/04 22:21:39 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int absolute_program(char *arg)
{
	return (ft_strchr(arg, '/') != NULL);
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
	
	if (absolute_program(arg))
		return (arg);
	path = ft_split(path_line, ':');
	if (!path)
	{
		ft_printf("%s: cannot malloc\n", arg); // fprintf作ろうね
		return (NULL);
	} 
	i = 0;
	while (path[i])
	{
		full_path = join_path_element(path[i], arg);
		if (!full_path)
		{
			ft_printf("%s: cannot malloc\n", arg); // fprintf作ろうね
			return (NULL);
		}
		if (!access(full_path, F_OK))
		{
			if (!access(full_path, X_OK))
			{
				free(path); // ちゃんと開放しようね
				return (full_path);
			}
		}
		i++;
	}
	// エラーメッセージをbashかzshどちらに合わせるのか考えよう
	free(path); // ここもね
	ft_printf("%s: command not found", arg);
	return (NULL);
	
}