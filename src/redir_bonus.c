/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:49:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/10 01:08:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int  here_document_to_fd(t_redirect *r)
{
	int herepipe[2];
	
	pipe(herepipe);
	if (!r->document)
		return (FALSE); // これは/dev/nullっぽいね
	// dup2(herepipe[1], 1);
	ft_putstr_fd(r->document, herepipe[1]); // 文字数が大きければファイルに一時書き込む
	close(herepipe[1]);
	return (herepipe[0]);
}

t_bool do_redirection(t_redirect *redirect)
{
	t_redirect *r;
	int fd;

	r = redirect;
	while (r)
	{
		if (r->instruction == e_input_direction)
		{
			fd = open(r->filename, O_RDONLY);
			if (fd == -1)
				return (ft_dprintf(stderr_fd, "pipex: no such file or directory: %s", r->filename), FALSE);
			dup2(fd, 0); // エラーチェック
			close(fd);
		}
		else if (r->instruction == e_output_direction)
		{
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd == -1)
				return (ft_dprintf(stderr_fd, "pipex: no such file or directory: %s", r->filename), FALSE);
			dup2(fd, 1); // エラーチェック
			close(fd);
		}
		r = r->next;
	}
	return (TRUE);
}