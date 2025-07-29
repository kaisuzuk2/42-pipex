/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:11:39 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/28 22:53:34 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// command_split_utils_bonus.c
int				count_remove_char(char const *s, char const *set);
char			*ft_strtrim_all(char const *s1, char const *set);
char			*get_trim_string(char *str);

static size_t	ft_word_count(char const *s)
{
	size_t	res;
	int		flg;
	char	quate;

	res = 0;
	flg = 1;
	quate = 0;
	while (*s)
	{
		if (!quate && ((*s == '\"') || (*s == '\'')))
			quate = *s;
		else if (*s == quate)
			quate = 0;
		else if (ft_isspace(*s) && !quate)
			flg = 1;
		else if (flg)
		{
			res++;
			flg = 0;
		}
		s++;
	}
	if (quate)
		return (0);
	return (res);
}

static char	*ft_extract_word(const char *p, int len)
{
	char	*tmp;
	char	*res;
	char	*set;

	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, p, len + 1);
	set = get_trim_string(tmp);
	res = ft_strtrim_all(tmp, set);
	free(set);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

static char	*ft_fill_word(char const **p)
{
	size_t	str_len;
	char	*res;
	char	quate;

	str_len = 0;
	quate = 0;
	while (ft_isspace(**p))
		(*p)++;
	while ((*p)[str_len])
	{
		if (!quate && ((*p)[str_len] == '\'' || (*p)[str_len] == '\"'))
			quate = (*p)[str_len];
		else if ((*p)[str_len] == quate)
			quate = 0;
		if (ft_isspace((*p)[str_len]) && !quate)
			break ;
		str_len++;
	}
	if (quate)
		return (NULL);
	res = ft_extract_word(*p, str_len);
	*p = *p + str_len;
	return (res);
}

static void	ft_free(char **current, char **head)
{
	while (--current > head)
		free(*current);
	free(current);
}

char	**command_split(char const *s)
{
	char	**head;
	char	**tmp;
	size_t	head_size;

	head_size = ft_word_count(s);
	head = (char **)malloc(sizeof(char *) * (head_size + 1));
	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp < &head[head_size])
	{
		*tmp = ft_fill_word(&s);
		if (*tmp == NULL)
		{
			ft_free(++tmp, head);
			return (NULL);
		}
		tmp++;
	}
	*tmp = NULL;
	return (head);
}
