/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quate_split_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:11:39 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:58:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char const *s, char c)
{
	size_t	res;
	int		flg;
	int		quate_flg;

	res = 0;
	flg = 1;
	quate_flg = 0;
	while (*s)
	{
		if (*s == '"')
			quate_flg = !quate_flg;
		else if (*s == c && !quate_flg)
			flg = 1;
		else if (flg)
		{
			res++;
			flg = 0;
		}
		s++;
	}
	return (res);
}

static char	*ft_extract_word(const char *p, int len)
{
	char	*tmp;
	char	*res;

	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, p, len + 1);
	res = ft_strtrim(tmp, "\"");
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

static char	*ft_fill_word(char const **p, char c)
{
	size_t	str_len;
	int		quate_flg;
	char	*res;

	str_len = 0;
	quate_flg = 0;
	while (**p == c)
		(*p)++;
	while ((*p)[str_len])
	{
		if ((*p)[str_len] == '"')
			quate_flg = !quate_flg;
		if ((*p)[str_len] == c && !quate_flg)
			break ;
		str_len++;
	}
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

char	**ft_quate_split(char const *s, char c)
{
	char	**head;
	char	**tmp;
	size_t	head_size;

	head_size = ft_word_count(s, c);
	head = (char **)malloc(sizeof(char *) * (head_size + 1));
	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp < &head[head_size])
	{
		*tmp = ft_fill_word(&s, c);
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
