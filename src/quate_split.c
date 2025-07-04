/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quate_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:11:39 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/02 23:21:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static size_t	ft_word_count(char const *s, char c)
{
	size_t	res;
	int		flg;

	res = 0;
	flg = 1;
	while (*s)
	{
		if (*s == c)
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

static char	*ft_fill_word(char const **p, char c)
{
	char	*res;
	size_t	str_len;

	str_len = 0;
	while (**p == c)
		(*p)++;
	while ((*p)[str_len])
	{
		if ((*p)[str_len] == c)
			break ;
		str_len++;
	}
	res = (char *)malloc(sizeof(char) * (str_len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, *p, str_len + 1);
	*p = *p + str_len;
	return (res);
}

static void	ft_free(char **current, char **head)
{
	while (--current > head)
		free(*current);
	free(current);
}

char	**quate_split(char const *s, char c)
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
		if (*tmp++ == NULL)
		{
			while (--tmp > head)
				free(tmp);
			free(head);
			return (NULL);
		}
		// tmp++;
	}
	*tmp = NULL;
	return (head);
}


// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "hello world this is a pen";
// 	char c = ' ';
// 	char **res = ft_split(str, c);
// 	if (res == NULL)
// 		return (0);
// 	for (int i = 0; res[i]; i++)
// 		printf("%s\n", res[i]);
// 	for (int i = 0; res[i]; i++)
// 		free(res[i]);
// 	free(res);
// }