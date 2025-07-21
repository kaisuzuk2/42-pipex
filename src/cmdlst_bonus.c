/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:04:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:59:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ft_quate_split_bonus.c
char		**ft_quate_split(char const *s, char c);

static void	set_fileredirect(t_redirect *r, enum e_instruction inst,
		char *filename)
{
	r->document = NULL;
	r->here_doc_eof = NULL;
	r->filename = filename;
	r->instruction = inst;
	r->next = NULL;
}

static void	set_here_doc(t_redirect *r, enum e_instruction inst,
		char *here_doc_eof, t_command *c)
{
	r->here_doc_eof = here_doc_eof;
	r->filename = NULL;
	r->instruction = inst;
	r->next = NULL;
	r->document = make_here_document(r, c);
}

void	cmdlst_add_back(t_command *head, t_command *new)
{
	t_command	*tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_command	*set_redirect(t_command *c, enum e_instruction inst,
		char *filename_eof)
{
	t_redirect	*r;

	r = (t_redirect *)malloc(sizeof(t_redirect));
	if (!r)
		return (NULL);
	if (inst == e_output_direction || inst == e_input_direction)
		set_fileredirect(r, inst, filename_eof);
	else if (inst == e_reading_until)
		set_here_doc(r, inst, filename_eof, c);
	else
		r = NULL;
	c->redirect = r;
	return (c);
}

t_command	*cmdnew(char *prog_name, char *cmds)
{
	t_command	*c;
	char		**cmdv;

	c = (t_command *)malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->prog_name = prog_name;
	cmdv = ft_quate_split(cmds, ' ');
	if (!cmdv)
		return (NULL);
	c->cmdv = cmdv;
	c->redirect = NULL;
	c->next = NULL;
	return (c);
}
