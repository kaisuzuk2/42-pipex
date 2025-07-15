/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:05:23 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/15 19:22:37 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"


// 環境変数の展開と文字数を返す
void heredoc_expand(t_redirect *r, size_t *lenp)
{
	*lenp = ft_strlen(r->document);
}

char *make_here_document(char *here_doc_eof, t_command *c)
{
	char *buf;
	char *document;
	char *tmp;
	int flg

	document = NULL;
	while (1)
	{
		ft_dprintf(STDOUT_FILENO, "> ");
		buf = get_next_line(0);
		if (!buf)
			break;
		if (ft_strncmp(buf, here_doc_eof, ft_strlen(here_doc_eof)) == 0 && buf[ft_strlen(here_doc_eof)] == '\n')
			break;
		if (!document)
		{
			document = ft_strdup(buf);
			if (document == NULL)
			{
				free(c);
				free(buf);
				sys_error("cannnot malloc");
				exit(EXECUTION_FAILURE);
			}
		}
		else
		{
			tmp = ft_strjoin(document, buf);
			if (!tmp)
			{
				free(c);
				free(document);
				free(buf);
				sys_error("cannnot malloc");
				exit(EXECUTION_FAILURE);
			}
			free(document);
			document = tmp;
		}
		free(buf);
	}
	return (document);
}