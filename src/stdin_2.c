/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 03:41:29 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 03:47:37 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char			*get_stdin(t_flags *f)
{
	t_get_stdin		z;

	z.buf_size = 0;
	z.head = create_node(READBUF);
	z.tmp = z.head;
	z.i = READBUF;
	while (z.i == READBUF)
	{
		z.i = 0;
		while (z.i < READBUF)
		{
			read(0, z.tmp->data + z.i, 1);
			if (z.tmp->data[z.i] == 0)
				break ;
			z.i++;
		}
		z.tmp->size = z.i;
		z.buf_size += z.i;
		z.prev = z.tmp;
		z.tmp = create_node(READBUF);
		z.prev->next = z.tmp;
	}
	f->size = z.buf_size;
	return (full_buffer(z.head, z.buf_size));
}
