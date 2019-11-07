/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharlet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:02:30 by kcharlet          #+#    #+#             */
/*   Updated: 2019/10/31 13:11:13 by kcharlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

char	*check_dwrstring(char *dwrstring, char **line)
{
	char *p2_line_feed;

	p2_line_feed = NULL;
	if (dwrstring)
		if ((p2_line_feed = ft_strchr(dwrstring, '\n')))
		{
			*p2_line_feed = '\0';
			*line = ft_strdup(dwrstring);
			ft_strcpy(dwrstring, ++p2_line_feed);
		}
		else
		{
			*line = ft_strdup(dwrstring);
			ft_strclr(dwrstring);
		}
	else
		*line = ft_strnew(1);
	return (p2_line_feed);
}

int		get_line(const int fd, char **line, char **dwrstring)
{
	char		buf[BUFF_SIZE + 1];
	int			b_w_r;
	char		*p1_line_feed;
	char		*tmp;

	p1_line_feed = check_dwrstring(*dwrstring, line);
	while (!p1_line_feed && (b_w_r = read(fd, buf, BUFF_SIZE)))
	{
		buf[b_w_r] = '\0';
		if ((p1_line_feed = ft_strchr(buf, '\n')))
		{
			*p1_line_feed = '\0';
			p1_line_feed++;
			*dwrstring = ft_strdup(p1_line_feed);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || b_w_r < 0)
			return (-1);
		ft_strdel(&tmp);
	}
	return (b_w_r || ft_strlen(*line)) ? 1 : 0;
}

t_list	*list_new_element(int fd)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->fd = fd;
	new->dwrstring = NULL;
	new->next = NULL;
	return (new);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (head == NULL)
		head = list_new_element(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = list_new_element(fd);
		tmp = tmp->next;
	}
	return (get_line(tmp->fd, line, &tmp->dwrstring));
}
