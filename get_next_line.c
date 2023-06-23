/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:29:13 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/23 14:16:10 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*rememo(char *memo)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (memo[i] != '\n' && memo[i] != '\0')
	{
		i++;
	}
	if (memo[i] == '\n')
		i++;
	while (i < ft_strlen(memo) && memo[i] != '\0')
	{
		memo[j] = memo[i];
		j++;
		i++;
	}
	memo[j] = '\0';
	return (memo);
}

char	*get_ans(char *memo)
{
	size_t	i;
	size_t	j;
	char	*ans;

	i = 0;
	j = 0;
	while (memo[i] != '\n' && memo[i] != '\0')
	{
		i++;
	}
	ans = (char *)malloc((i + 2) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	while (j < i)
	{
		ans[j] = memo[j];
		j++;
	}
	ans[j] = '\0';
	return (ans);
}

char	*get_memo(int fd, char *memo)
{
	char	*buf;
	ssize_t	done;

	done = 1;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (done > 0 && ft_strchr(memo, '\n') == 0)
	{
		done = read(fd, buf, BUFFER_SIZE);
		if (done == -1 || buf[0] == '\0')
		{
			free(buf);
			buf = NULL;
			return (NULL);
		}
		if (memo == NULL || memo[0] == '\0')
			*memo = '\0';
		buf[done] = '\0';
		memo = my_strjoin(memo, buf);
	}
	free(buf);
	buf = NULL;
	return (memo);
}

char	*get_next_line(int fd)
{
	static char	*memo;
	char		*ans;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	if (memo == NULL)
		memo = (char *)malloc((30) * sizeof(char));
	if (memo == NULL)
		return (NULL);
	memo = get_memo(fd, memo);
	if (memo == NULL)
		return (NULL);
	ans = get_ans(memo);
	memo = rememo(memo);
	return (ans);
}
