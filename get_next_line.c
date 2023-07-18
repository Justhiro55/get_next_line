/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:29:13 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/28 20:09:34 by hhagiwar         ###   ########.fr       */
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
		i++;
	if (memo[i] == '\0')
	{
		free(memo);
		memo = NULL;
		return (NULL);
	}
	if (memo[i] == '\n')
		i++;
	while (memo[i] != '\0')
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
	if (!memo[i])
		return (NULL);
	while (memo[i] != '\n' && memo[i] != '\0')
		i++;
	ans = (char *)malloc((i + 2) * sizeof(char));
	if (ans == NULL)
		return (ft_free(&memo));
	while (j < i)
	{
		ans[j] = memo[j];
		j++;
	}
	if (memo[j] && memo[i] == '\n')
	{
		ans[j] = '\n';
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
		if (done == -1)
		{
			free(buf);
			free(memo);
			return (NULL);
		}
		buf[done] = '\0';
		memo = my_strjoin(memo, buf);
		if (memo == NULL)
			break ;
	}
	free(buf);
	buf = NULL;
	return (memo);
}

char	*get_next_line(int fd)
{
	static char	*memo;
	char		*ans;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (memo == NULL)
	{
		memo = (char *)malloc(sizeof(char));
		if (memo == NULL)
			return (NULL);
		memo[0] = '\0';
	}
	memo = get_memo(fd, memo);
	if (memo == NULL)
		return (NULL);
	ans = get_ans(memo);
	if (memo == NULL)
		return (NULL);
	memo = rememo(memo);
	return (ans);
}
