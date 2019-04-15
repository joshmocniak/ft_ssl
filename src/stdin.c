/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:41:10 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/05 20:18:33 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_list_			*create_node(int data_size)
{
	t_list_	*tmp;

	tmp = (t_list_ *)ft_memalloc(sizeof(t_list_));
	tmp->data = (char *)ft_memalloc(sizeof(char) * data_size);
	tmp->next = 0;
	tmp->size = 0;
	return (tmp);
}

void			free_node(t_list_ *node)
{
	free(node->data);
	free(node);
}

char			*full_buffer(t_list_ *node, int buf_size)
{
	t_list_	*prev;
	char	*buf;
	int		i;

	i = 0;
	buf = (char *)ft_memalloc(sizeof(char) * (buf_size + 1));
	prev = node;
	while (node->size > 0)
	{
		ft_memcpy(buf + i, node->data, node->size);
		prev = node;
		node = node->next;
		free_node(prev);
		i += READBUF;
	}
	free_node(node);
	return (buf);
}

static void		cleanup(t_list_ *head)
{
	t_list_		*prev;

	while (head->size > 0)
	{
		prev = head;
		head = head->next;
		free_node(prev);
	}
	free_node(head);
}

char			*read_to_buffer(char *filename, int fd, t_flags *f)
{
	t_list_	*head;
	t_list_	*tmp;
	t_list_	*prev;
	int		buf_size;

	if (fd == 0)
		return (get_stdin(f));
	buf_size = 0;
	head = create_node(READBUF);
	tmp = head;
	while ((tmp->size = read(fd, tmp->data, READBUF)) > 0)
	{
		buf_size += tmp->size;
		prev = tmp;
		tmp = create_node(READBUF);
		prev->next = tmp;
	}
	if (tmp->size == -1)
	{
		modified_strerror(filename, f);
		cleanup(head);
		return (0);
	}
	f->size = buf_size;
	return (full_buffer(head, buf_size));
}
