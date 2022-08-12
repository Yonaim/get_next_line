/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:47:46 by yona              #+#    #+#             */
/*   Updated: 2022/08/04 14:48:37 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_lf_idx(t_buff *buf)
{
	int	idx;

	idx = buf->offset;
	while (idx < buf->rbytes)
	{
		if (buf->str[idx] == '\n')
		{
			buf->lf_idx = idx;
			return (idx);
		}
		idx++;
	}
	buf->lf_idx = FAIL;
	return (FAIL);
}

char	*append_buf_to_line(t_line *line, t_buff *buf, int start, int end)
{
	char	*dst;
	int		i;

	if (start > end && line->str == NULL)
		return (NULL);
	if (start > end)
		dst = malloc(sizeof(char) * (line->len + 1));
	else
		dst = malloc(sizeof(char) * (line->len + (end - start + 1) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (++i < line->len)
		dst[i] = line->str[i];
	i = -1;
	while (++i <= (end - start))
		dst[line->len + i] = buf->str[start + i];
	line->len += (end - start + 1);
	if (line->str)
		free(line->str);
	line->str = NULL;
	return (dst);
}

char	*final_append_and_complete_line(t_line *line, t_buff *buf, \
int start, int end)
{
	char	*dst;

	dst = append_buf_to_line(line, buf, start, end);
	if (!dst)
		return (NULL);
	dst[line->len] = '\0';
	buf->offset = end + 1;
	return (dst);
}

int	do_read_next(int fd, t_buff *buf, t_line *line)
{
	buf->rbytes = read(fd, buf->str, BUFFER_SIZE);
	if (buf->rbytes <= 0)
	{
		if (buf->rbytes == -1 && line->str)
			free(line->str);
		buf->offset = BUFFER_SIZE + 1;
		return (FAIL);
	}
	else
	{
		buf->offset = 0;
		return (SUCCESS);
	}
}
