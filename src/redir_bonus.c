/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:49:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/16 00:51:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	sh_mktmpfd(const char *nameroot, char *filename)
{
	filename = ft_strjoin("tmp/", nameroot);
	if (!filename)
		return (-1);
	return (ft_mkstemp(filename));
}

static int	here_document_to_fd(t_redirect *r)
{
	int		herepipe[2];
	size_t	document_len;
	int		fd;
	char	filename;

	heredoc_expand(r, &document_len);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			return (EXECUTION_FAILURE); // エラー処理
		return (fd);
	}
	else if (document_len <= HEREDOC_PIPESIZE)
	{
		if (pipe(herepipe) < 0)
			return (sys_error("heredoc_error"), EXECUTION_FAILURE);
		ft_putstr_fd(r->document, herepipe[1]);
		close(herepipe[1]);
		return (herepipe[0]);
	}
	else
	{
		fd = sh_mktmpfd("sh-thd", &filename);
		if (fd == -1)
			return (EXECUTION_FAILURE);
		ft_putstr_fd(r->document, fd);
		return (fd);
	}
}

// それぞれのファイルで権限がなかったときの処理を考えよう
// 出力リダイレクト先が元から用意されていた場合のケースはどうかね
static int	do_redirection_internal(char *prog_name, t_redirect *redirect)
{
	t_redirect	*r;
	int			fd;
	int			to_fd;

	r = redirect;
	while (r)
	{
		if (r->instruction == e_input_direction)
		{
			fd = open(r->filename, O_RDONLY);
			to_fd = 0;
		}
		else
		{
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			to_fd = 1;
		}
		if (fd == -1)
			return (internal_error(prog_name, r->filename, strerror(errno)),
				EXECUTION_FAILURE);
		if (dup2(fd, to_fd) < 0)
			return (sys_error(r->filename), EXECUTION_FAILURE);
		close(fd);
		r = r->next;
	}
	return (EXECUTION_SUCCESS);
}

int	do_redirections(char *prog_name, t_redirect *redirect)
{
	int here_fd;

	if (redirect->instruction == e_input_direction
		|| redirect->instruction == e_output_direction)
		if (do_redirection_internal(prog_name, redirect) == EXECUTION_FAILURE)
			return (EXECUTION_FAILURE);
	if (redirect->instruction == e_reading_until)
	{
		here_fd = here_document_to_fd(redirect);
		if (here_fd == EXECUTION_FAILURE)
			return (EXECUTION_FAILURE);
		if (dup2(here_fd, 0) < 0)
			return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}