/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:09:27 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/01/03 13:24:15 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_buff	*fetch_correct_buff(t_buff **head, int fd)
{
	t_buff	*cur;

	cur = *head;
	while (cur && cur->fd != fd)
		cur = cur->next;
	if (!cur)
	{
		cur = malloc(sizeof(t_buff));
		if (!cur)
			return (NULL);
		cur->fd = fd;
		cur->lf_idx = 0;
		cur->offset = 0;
		cur->rbytes = 0;
		cur->next = *head;
		*head = cur;
	}
	return (cur);
}

void	delete_this_buff(t_buff *del, t_buff **head)
{
	t_buff	*prev;

	if (del == *head)
	{
		*head = del->next;
		free(del);
	}
	else
	{
		prev = *head;
		while (prev->next && prev->next != del)
			prev = prev->next;
		prev->next = del->next;
		free(del);
	}
}

char	*get_next_line(int fd)
{
	static t_buff	*head;
	t_buff			*buf;
	t_line			line;

	line.str = NULL;
	line.len = 0;
	buf = fetch_correct_buff(&head, fd);
	if (!buf)
		return (NULL);
	while (get_next_lf_idx(buf) == FAIL)
	{
		line.str = append_buf_to_line(&line, buf, buf->offset, buf->rbytes - 1);
		if (do_read_next(fd, buf, &line) == FAIL)
		{
			if (buf->rbytes == -1 || (line.str == NULL && buf->rbytes == 0))
				line.str = NULL;
			if (buf->rbytes < BUFFER_SIZE && get_next_lf_idx(buf) == FAIL)
				line.str = final_complete_line(&line, buf, 0, buf->rbytes - 1);
			delete_this_buff(buf, &head);
			return (line.str);
		}
	}
	return (final_complete_line(&line, buf, buf->offset, buf->lf_idx));
}
