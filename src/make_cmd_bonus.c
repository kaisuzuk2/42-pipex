/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:05:23 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/16 00:33:05 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 環境変数の展開と文字数を返す
void	heredoc_expand(t_redirect *r, size_t *lenp)
{
	*lenp = ft_strlen(r->document);
}

static char	*documentcat(char *document, char *buf)
{
	char	*tmp;

	if (!document)
	{
		document = ft_strdup(buf);
		if (!document)
			return (NULL);
	}
	else
	{
		tmp = ft_strjoin(document, buf);
		free(document);
		if (!tmp)
			return (NULL);
		document = tmp;
	}
	return (document);
}

char	*make_here_document(t_redirect *r, t_command *c)
{
	char *buf;
	char *document;
	const char *here_doc_eof = r->here_doc_eof;

	document = NULL;
	while (1)
	{
		ft_dprintf(STDOUT_FILENO, "> ");
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (ft_strncmp(buf, here_doc_eof, ft_strlen(here_doc_eof)) == 0
			&& buf[ft_strlen(here_doc_eof)] == '\n')
		{
			free(buf);
			break;
		}
		document = documentcat(document, buf);
		free(buf);
		if (!document)
		{
			free(c);
			free(r);
			sys_error("cannnot malloc");
			exit(EXECUTION_FAILURE);
		}
	}
	return (document);
}