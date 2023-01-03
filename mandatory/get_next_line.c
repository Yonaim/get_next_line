/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:09:27 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/01/03 13:24:10 by yeonhkim         ###   ########.fr       */
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
