/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharlet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:00:57 by kcharlet          #+#    #+#             */
/*   Updated: 2019/10/31 13:09:37 by kcharlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"

# define BUFF_SIZE 50

typedef	struct	s_list
{
	int				fd;
	char			*dwrstring;
	struct s_list	*next;
}				t_list;

int				get_next_line(const int fd, char **line);

#endif
