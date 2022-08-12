/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:51:55 by yeonhkim          #+#    #+#             */
/*   Updated: 2022/08/13 00:29:53 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*------------------ HEADERS ---------------------*/

# include <unistd.h>
# include <stdlib.h>

/*----------- DEFINE SYMBOLIC CONSTANTS -----------*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define FAIL -1
# define SUCCESS 0

/*------------- STRUCT DECLARATIONS --------------*/

typedef struct s_buff
{
	int				fd;
	char			str[BUFFER_SIZE];
	int				lf_idx;
	int				offset;
	int				rbytes;
	struct s_buff	*next;
}	t_buff;

typedef struct s_line
{
	char	*str;
	int		len;
}	t_line;

/*-------------- FUNCTION PROTOTYPES -------------*/

int		get_next_lf_idx(t_buff *buf);
char	*append_buf_to_line(t_line *line, t_buff *buf, int start, int end);
char	*final_complete_line(t_line *line, t_buff *buf, int start, int end);
int		do_read_next(int fd, t_buff *buf, t_line *line);
char	*get_next_line(int fd);
t_buff	*fetch_correct_buff(t_buff **head, int fd);
void	delete_this_buff(t_buff *del, t_buff **head);

#endif