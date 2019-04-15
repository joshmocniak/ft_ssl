/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_body_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:24:54 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 12:44:10 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_u32			get(t_md5_ctx *c, int n)
{
	return (c->block[(n)]);
}

t_u32			set(t_md5_ctx *c, t_md5_abcd *z, int n)
{
	c->block[(n)] = (t_u32)z->ptr[(n) * 4] | \
					((t_u32)z->ptr[(n) * 4 + 1] << 8) | \
					((t_u32)z->ptr[(n) * 4 + 2] << 16) | \
					((t_u32)z->ptr[(n) * 4 + 3] << 24);
	return (c->block[(n)]);
}

static void		rotate(t_md5_abcd *z)
{
	t_u32		tmp;

	tmp = z->d;
	z->d = z->c;
	z->c = z->b;
	z->b = z->a;
	z->a = tmp;
}

void			step(t_step *y, t_md5_abcd *z)
{
	(z->a) += y->f((z->b), (z->c), (z->d)) + (y->x) + (y->t);
	(z->a) = (((z->a) << (y->s)) | (((z->a) & 0xffffffff) >> (32 - (y->s))));
	(z->a) += (z->b);
	rotate(z);
}
