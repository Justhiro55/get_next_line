/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:29:13 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/22 15:39:30 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*rememo(char *memo)
{
	int	i;
	int	j;

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
	int		i;
	int		j;
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
		if (done == -1)
		{
			return (NULL);
		}
		if (memo == NULL)
			*memo = '\0';
		buf[done] = '\0';
		memo = my_strjoin(memo, buf);
	}
	free(buf);
	return (memo);
}

char	*get_next_line(int fd)
{
	static char	*memo;
	char		*ans;

	if (BUFFER_SIZE < 0)
		return (NULL);
	if (memo == NULL)
		memo = (char *)malloc((100) * sizeof(char));
	if (memo == NULL)
		return (NULL);
	memo = get_memo(fd, memo);
	printf("check : get_memo\n%s\n\n", memo);
	ans = get_ans(memo);
	printf("check : get_ans\n%s\n\n", ans);
	memo = rememo(memo);
	printf("check : rememo\n%s\n\n------------------------------------------\n",
			memo);
	return (ans);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

int	main(void)
{
	int		fd;
	char	*line1;
	char	*line2;
	char	*line3;
	char	*line4;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file.\n");
		return (-1);
	}
	line1 = get_next_line(fd);
	if (line1 != NULL)
	{
		printf("Line read1:%s\n-----------------------------------------------------------\n",
				line1);
		free(line1);
	}
	line2 = get_next_line(fd);
	if (line2 != NULL)
	{
		printf("Line read2:%s\n-----------------------------------------------------------\n",
				line2);
		free(line2);
	}
	line3 = get_next_line(fd);
	if (line3 != NULL)
	{
		printf("Line read2:%s\n-----------------------------------------------------------\n",
				line3);
		free(line3);
	}
	line4 = get_next_line(fd);
	if (line4 != NULL)
	{
		printf("Line read2:%s\n-----------------------------------------------------------\n",
				line4);
		free(line4);
	}
	close(fd);
	return (0);
}
