/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:09:27 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/02 04:58:45 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_internal.h"

static void	do_read_next(int fd, t_buff *buf, int *fd_stat)
{
	const int	rbytes = read(fd, buf->str, BUFFER_SIZE);

	if (rbytes == -1)
		*fd_stat = INVALID;
	else if (rbytes < BUFFER_SIZE)
		*fd_stat = EOF_REACHED;
	else
		*fd_stat = NORMAL;
	buf->rbytes = rbytes;
	buf->offset = 0;
}

static char	*final_complete_line(t_line *line, t_buff *buf, int lf_exist)
{
	int	start;
	int	end;

	if (lf_exist)
	{
		start = buf->offset;
		end = buf->lf_idx;
	}
	else
	{
		start = 0;
		end = buf->rbytes - 1;
	}
	append_buf_to_line(line, buf, start, end);
	if (!line->str)
		return (NULL);
	line->str[line->len] = '\0';
	return (line->str);
}

char	*get_next_line(int fd)
{
	static struct s_buff	buf;
	struct s_line			line;
	int						fd_stat;

	line.str = NULL;
	line.len = NO_CONTENT;
	while (find_next_lf_idx(&buf) == FAILURE)
	{
		append_buf_to_line(&line, &buf, buf.offset, buf.rbytes - 1);
		do_read_next(fd, &buf, &fd_stat);
		if (fd_stat == INVALID)
		{
			free(line.str);
			return (NULL);
		}
		else if (fd_stat == EOF_REACHED)
		{
			if (line.len == NO_CONTENT && buf.rbytes == NO_CONTENT)
				return (NULL);
			else if (find_next_lf_idx(&buf) == FAILURE)
				return (final_complete_line(&line, &buf, LF_NONE));
		}
	}
	return (final_complete_line(&line, &buf, LF_EXIST));
}
