/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:09:27 by yeonhkim          #+#    #+#             */
/*   Updated: 2022/08/04 14:48:22 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buff	buf;
	t_line			line;

	line.str = NULL;
	line.len = 0;
	while (get_next_lf_idx(&buf) == FAIL)
	{
		line.str = append_buf_to_line(&line, &buf, buf.offset, buf.rbytes - 1);
		if (do_read_next(fd, &buf, &line) == FAIL)
		{
			if (buf.rbytes == -1 || (line.str == NULL && buf.rbytes == 0))
				return (NULL);
			if (buf.rbytes < BUFFER_SIZE && get_next_lf_idx(&buf) == FAIL)
				return (final_append_and_complete_line(&line, &buf, 0, \
				buf.rbytes - 1));
		}
	}
	return (final_append_and_complete_line(&line, &buf, buf.offset, \
	buf.lf_idx));
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	int fd1 = open("test1", O_RDONLY);
// 	//int fd2 = open("test2.txt", O_RDONLY);
// 	if(fd1)
// 		;
// 	for(int i = 0; i < 10; i++)
// 	{
// 		char *line = get_next_line(fd1);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	system("leaks a.out");
// }